import 'package:twittermostfollowed/data/user.dart';
import 'package:twittermostfollowed/data/fetch.dart';
import 'dart:collection';
import 'dart:math';



class UserData {
  String status = '';
  List<User> _users = [];
  Map friendMap = new Map();
  Map inverted = new Map();
  List mostFollowed = [];
  List mostRecentlyFollowed = [];
  List mostTweeted = [];
  List mostFavorited = [];
  List mostLiked = [];
  List mostRecentlyLiked = [];
  List tweetList = [];
  List likeList = [];
  List recentlyLikedList = [];
  List dbUsers = [];
  Map dbMap = new Map();
  List leadUsers = [];
  Map userInfoMap = new Map();


  UnmodifiableListView<User> get list {
    return UnmodifiableListView(_users);
  }

  Future getDataBase () async {
    Fetch dbFetch = Fetch(url: 'get_db', json: {});
    var list = await dbFetch.getData();
    print(list.length);
    status = "Database";
    for (var j=0; j<list.length; j+=90) {
      print(j);
      var tempList = j+90>list.length? list.sublist(j,list.length) : list.sublist(j,j+90);
      var requestStr = tempList.map((x)=>(x[3])).join(",");
      Fetch userFetch = Fetch(url: 'user_info', json: {'user_string':requestStr});
      var userData = await userFetch.getData();
      for (var i=0; i<userData.length; i++) {
        var target = tempList.where((x)=>x[0]==userData[i]['screen_name'].toLowerCase());
        var newUser = User(
          screenName: userData[i]['screen_name'].toLowerCase(),
          id: userData[i]['id'].toString(),
          fullName: userData[i]['name'],
          bio: userData[i]['description'],
          friendsCount: userData[i]['friends_count'],
          followersCount: userData[i]['followers_count'],
          img: userData[i]['profile_image_url'],
          location: userData[i]['location'],
        );
        dbUsers.add(newUser);
        dbMap[newUser] = target.elementAt(0).elementAt(1).split(",");
      }
      for (var name in tempList.where((x)=>!dbUsers.map((x)=>x.screenName.toLowerCase()).contains(x[0])).map((x)=>x[0])) {
        Fetch fetch = Fetch(url: 'screen', json: {'handle': name});
        var userData = await fetch.getData();
        var target = tempList.where((x) =>
        x[0] == userData[0]['screen_name'].toLowerCase());
        var newUser = User(
          screenName: userData[0]['screen_name'].toLowerCase(),
          id: userData[0]['id'].toString(),
          fullName: userData[0]['name'],
          bio: userData[0]['description'],
          friendsCount: userData[0]['friends_count'],
          followersCount: userData[0]['followers_count'],
          img: userData[0]['profile_image_url'],
          location: userData[0]['location'],
        );
        dbUsers.add(newUser);
        dbMap[newUser] = target.elementAt(0).elementAt(1).split(",");
      }
    }
    dbUsers.sort((a,b)=>a.fullName.toLowerCase().compareTo(b.fullName.toLowerCase()));
    return true;
  }

  Future getLeader() async {
    status = "Leaderboard";
    Fetch dbFetch = Fetch(url: 'get_leaderboard', json: {});
    var list = await dbFetch.getData();
      var requestStr = list.map((x) => (x[0])).join(",");
      Fetch userFetch = Fetch(
          url: 'user_info', json: {'user_string': requestStr});
      var userData = await userFetch.getData();
      for (var i = 0; i < userData.length; i++) {
        var target = list.where((x) => x[0] == userData[i]['id'].toString());
        print(target.elementAt(0).elementAt(0));
        var newUser = User(
            screenName: userData[i]['screen_name'].toLowerCase(),
            id: userData[i]['id'].toString(),
            fullName: userData[i]['name'],
            bio: userData[i]['description'],
            friendsCount: userData[i]['friends_count'],
            followersCount: userData[i]['followers_count'],
            img: userData[i]['profile_image_url'],
            location: userData[i]['location'],
            followedBy: target.elementAt(0).elementAt(1)
        );
        leadUsers.add(newUser);
      }
    leadUsers.sort((a,b)=>b.followedBy.length.compareTo(a.followedBy.length));
  }

  addDBUSer(User dbuser) {
    if(!_users.map((x)=>x.screenName.toLowerCase()).contains(dbuser.screenName.toLowerCase())) {
      _users.add(dbuser);
    } else {
      _users.remove(_users.where((x)=>x.screenName.toLowerCase()==dbuser.screenName.toLowerCase()).elementAt(0));
    }
  }

  Future<List<dynamic>> addUser(reqUser) async {
    int count = 0;
    Fetch fetch = Fetch(url: 'screen', json: {'handle':reqUser});
    var userData = await fetch.getData();
    try {
      if (userData[0]['friends_count']<5) {
        return [false,"${userData[0]['name']} doesn't follow enough users."];
      } else if (userData[0]['friends_count']>30000) {
        return [false,"${userData[0]['name']} follows over 30K users."];
      } else if (_users.map((x)=>x.screenName).contains(userData[0]['screen_name'])){
        return [false, "${userData[0]['name']} already added."];
      } else if (count>10) {
        return [false, "Sorry, Twitter won't allow that many at once."];
      } else {

        var newUser = User(
          screenName: userData[0]['screen_name'].toLowerCase(),
          id: userData[0]['id'].toString(),
          fullName: userData[0]['name'],
          bio: userData[0]['description'],
          friendsCount: userData[0]['friends_count'],
          followersCount: userData[0]['followers_count'],
          img: userData[0]['profile_image_url'],
          location: userData[0]['location'],
        );
        _users.add(newUser);
        count++;

        return [true,"${userData[0]['name']} was added.",_users];
      }
    } catch (e) {
      return [false,"$reqUser is an invalid user."];
    }
  }

  List<User> deleteUser(User delUser) {
    _users.remove(delUser);
    return _users;
  }

  Future getFriendList (User user, int cursor, List startList) async {
    if (dbMap.keys.contains(user)) {
      friendMap[user] = dbMap[user];
    } else {
      Fetch fetch = Fetch(url: 'friends_id', json: {'handle':user.screenName, 'cursor':cursor});
      var friendData = await fetch.getData();
      try {
        List twitList = friendData['ids'];
        List newList = startList + twitList;
        if (friendData['next_cursor']==0) {
          friendMap[user] = newList.map((x)=>x.toString());
        } else {
          await getFriendList(user, friendData['next_cursor'], newList.sublist(0,newList.length-1));
        }
      } catch (e) {
        print(e);
      }
    }
  }

  Future getUserInfo (String userid) async {
    Fetch fetch = Fetch(url: 'user_info', json: {'user_string':userid});
    var userData = await fetch.getData();
    var list = [];
    for (int i=0; i<userData.length; i++) {
      try {
        var newUser = User(
          screenName: userData[i]['screen_name'].toLowerCase(),
          id: userData[i]['id'].toString(),
          fullName: userData[i]['name'],
          bio: userData[i]['description'],
          friendsCount: userData[i]['friends_count'],
          followersCount: userData[i]['followers_count'],
          img: userData[i]['profile_image_url'],
          location: userData[i]['location'],
          followedBy: inverted[userData[i]['id'].toString()],
        );
        userInfoMap[newUser.id]=newUser;
        list.add(newUser);
        status = "${newUser.screenName}'s Information";
      } catch (e) {
        return;
      }
    }
    return list;
  }

  Future getTweets (String userid, bool fav) async {
    String x = fav ? 'favorites':'tweets';
    Fetch fetch = Fetch(url: x, json: {'user_id': userid});
    var tweetData = await fetch.getData();
    var tlist = [];
    for (var item in tweetData) {
      var newTweet = Tweet(
        screenName: item['user']['screen_name'],
        id: item['user']['id'].toString(),
        fullName: item['user']['name'],
        tweet: item['text'],
        twitid: item['id_str'],
        reTweetCount: item['retweet_count'],
        favoriteCount: item['favorite_count'],
        img: item['user']['profile_image_url'],
        createdAt: item['created_at'].split(' ')[1] + " " + item['created_at'].split(' ')[2] + " " + item['created_at'].split(' ')[5],
      );
      tlist.add(newTweet);
    }
    return tlist;
  }

  Future processData() async {
    inverted.clear();
    mostFollowed = [];
    mostRecentlyFollowed = [];
    mostTweeted = [];
    mostFavorited = [];
    mostLiked = [];
    mostRecentlyLiked = [];
    tweetList = [];
    likeList = [];
    recentlyLikedList = [];

    var matchList = friendMap.keys;
    var filtered = [];
    for (var item in _users) {
      if (!matchList.contains(item)) {
        filtered.add(item);
      }
    }
    await Future.wait(filtered.map((user)=>getFriendList(user, -1, [])));
    if (_users.map((user) => friendMap.keys.contains(user)).contains(false)) {
      return "Sorry, Rate Limited.";
    } else {
      var topFollowed = invert(_users);
      var topRecent = _users.map((user)=>[user, friendMap[user].toList().sublist(0,10)]);
      var followedRequestStr = topFollowed.map((item)=>item[0]).join(",");
      List mostFollowedRaw = await getUserInfo(followedRequestStr);
      mostFollowed = clean(mostFollowedRaw);
      mostRecentlyFollowed = await recentBuild(topRecent);

      for (int i=0;i<_users.length;i++) {
        List x = await getTweets(_users[i].id, false);
        status = "${_users[i].fullName}'s Tweets";
        tweetList = tweetList + x;
      }

      tweetList.sort((a,b)=>b.reTweetCount.compareTo(a.reTweetCount));
      mostTweeted = tweetList.sublist(0,20);
      tweetList.sort((a,b)=>b.favoriteCount.compareTo(a.favoriteCount));
      mostFavorited = tweetList.sublist(0,20);

      for (int i=0;i<_users.length;i++) {
        status = "${_users[i].fullName}'s Likes";
        List y = await getTweets(_users[i].id, true);
        likeList = likeList + y;
        print(y);
        mostRecentlyLiked.add([_users[i],y.sublist(0,[5,y.length].reduce(min))]);
        print(_users[i].screenName);
      }

      likeList.sort((a,b)=>b.favoriteCount.compareTo(a.favoriteCount));
      mostLiked = likeList.sublist(0,[20,likeList.length].reduce(min));

      return "Analysis Complete.";
    }

  }

  Future<List> recentBuild(list) async{
    var out = [];
    for(var item in list) {
      status = "${item[0].fullName}'s Recent Followings";
      var x = await getRecent(item[1]);
      out.add([item[0],x]);
    }
    return out;
  }

  Future<List> getRecent(List list) async {
    var recentRequestStr = list.join(",");
    var x = await getUserInfo(recentRequestStr);
    return clean(x).sublist(0,5);
  }

  List clean(list) {
    var x = [];
    for (var item in list) {
    if (!(item==null)) {
      x.add(item);
    }
    }
    return x;
  }

  List invert(userList) {
    status = " Mutual Followings";
    for (var user in userList) {
      var list = friendMap[user];
      print(list);
      for (var num in list) {
        if (inverted.keys.contains(num)) {
          var entry = inverted[num];
          entry.add(user.screenName);
        } else {
          inverted[num] = [user.screenName];
        }
      }
    }
    List outList = [];
    for (var entry in inverted.entries) {
      outList.add([entry.key, entry.value]);
    }

    outList.sort((a,b)=>b[1].length.compareTo(a[1].length));
    return outList.sublist(0,20);
  }
}




