import 'package:flutter/material.dart';
import 'package:twittermostfollowed/data/user.dart';
import 'package:flutter_slidable/flutter_slidable.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';

String countClean(n) {
  if (n>=1000000) {
    return (((n/100000).round()/10).toString()+" MM");
  } else if (n>=100000) {
    return ((n/1000).round().toString()+ " K");
  } else if (n>=1000) {
    return (((n/100).round()/10).toString()+ " K");
  } else {
    return n.toString();
  }
}

class UserTile extends StatelessWidget {

  UserTile({@required this.user, this.delFunction});
  final User user;
  final Function delFunction;

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 8.0, vertical: 4.0),
      child: Slidable(
        actionPane: SlidableDrawerActionPane(),
        actionExtentRatio: 0.1,
        child: Container(
          color: Color(0XFF121F2F),
          height: 60,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: <Widget>[
              Padding(
                padding: const EdgeInsets.only(left: 8.0, right: 12),
                child: CircleAvatar(
                  backgroundImage: NetworkImage(user.img),
                  radius: 18,
                ),
              ),
              Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                mainAxisAlignment: MainAxisAlignment.center,
                children: <Widget>[
                  Container(
                    width: 130,
                    child: Text(user.fullName,
                      maxLines:1,
                      softWrap: false,
                      overflow: TextOverflow.fade,
                      style: TextStyle(
                        color: Colors.white,
                        fontWeight: FontWeight.bold,
                      ),),
                  ),
                  Text("@${user.screenName}",
                    style: TextStyle(
                      color: Colors.blueGrey,
                    ),
                  )
                ],
              ),
              Expanded(
                child: Container(),
              ),
              Column(
                crossAxisAlignment: CrossAxisAlignment.end,
                mainAxisAlignment: MainAxisAlignment.center,
                children: <Widget>[
                  Text(countClean(user.friendsCount),
                      style: TextStyle(color: Colors.white)),
                  Text(countClean(user.followersCount),
                      style: TextStyle(color: Colors.white)),
                ],
              ),
              SizedBox(
                width: 10,
              ),
              Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                mainAxisAlignment: MainAxisAlignment.center,
                children: <Widget>[
                  Text("Following",
                      style: TextStyle(color: Colors.blueGrey)),
                  Text("Followers",
                      style: TextStyle(color: Colors.blueGrey)),
                ],
              ),
              Padding(
                padding: const EdgeInsets.only(left: 10.0),
                child: Icon(Icons.keyboard_arrow_left,color: Colors.white,
                ),
              ),
            ],
          ),
        ),
        secondaryActions: <Widget>[
          IconSlideAction(
            color: Color(0XFF0F1926),
            iconWidget: Icon(Icons.remove_circle_outline, color: Color(0XFF453F5F)),
            onTap: delFunction,
          ),
        ],
      ),
    );
  }
}


class DBTile extends StatefulWidget {
  DBTile({@required this.user, this.addFunction, this.added});
  final User user;
  final bool added;
  final Function addFunction;

  @override
  _DBTileState createState() => _DBTileState();
}

class _DBTileState extends State<DBTile> {
  var set = false;
  var count = 0;

  void addMe(user) {
    widget.addFunction(user);
    setState(() {
      set = !set;
      count++;
    });
  }

  @override
  Widget build(BuildContext context) {
    return InkWell(
      onTap: () {addMe(widget.user);},
      child: Container(
        color: (count==0? widget.added : (widget.added? !set : set))? Color(0XFF121F2F) : Color(0XFF122F3F),
        height: 60,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.only(left: 8.0, right: 12),
              child: CircleAvatar(
                backgroundImage: NetworkImage(widget.user.img),
                radius: 18,
              ),
            ),
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Container(
                  width: 140,
                  child: Text(widget.user.fullName,
                    maxLines:1,
                    softWrap: false,
                    overflow: TextOverflow.fade,
                    style: TextStyle(
                      color: Colors.white,
                      fontWeight: FontWeight.bold,
                      fontSize: 13,
                    ),),
                ),
                Text("@${widget.user.screenName}",
                  style: TextStyle(
                    color: Colors.blueGrey[300],
                    fontSize: 13,
                  ),
                )
              ],
            ),
            Expanded(
              child: Container(),
            ),
            Column(
              crossAxisAlignment: CrossAxisAlignment.end,
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Text(countClean(widget.user.friendsCount),
                    style: TextStyle(color: Colors.white, fontSize: 13, fontWeight: FontWeight.w700)),
                Text(countClean(widget.user.followersCount),
                    style: TextStyle(color: Colors.white, fontSize: 13, fontWeight: FontWeight.w700)),
              ],
            ),
            SizedBox(
              width: 10,
            ),
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Text("Following",
                    style: TextStyle(color: Colors.blueGrey[200], fontSize: 13)),
                Text("Followers",
                    style: TextStyle(color: Colors.blueGrey[200], fontSize: 13)),
              ],
            ),
            Padding(
              padding: const EdgeInsets.only(left: 10.0, right: 10.0, bottom:15),
              child: Icon((count==0? widget.added : (widget.added? !set : set))? Icons.playlist_add_check : Icons.library_add,color: Colors.blueGrey[200], size:14,
              ),
            ),
          ],
        ),
      ),
    );
  }
}


class FollowedTile extends StatelessWidget {

  FollowedTile({@required this.user});
  final User user;

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 8.0, vertical: 4.0),
      child: Container(
        color: Color(0XFF121F2F),
        height: user.bio==''? 80: 115,
        child: Column(
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 2.0, vertical: 8),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: <Widget>[
                  Padding(
                    padding: const EdgeInsets.only(left: 8.0, right: 12),
                    child: CircleAvatar(
                      backgroundImage: NetworkImage(user.img),
                      radius: 18,
                    ),
                  ),
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: <Widget>[
                      Container(
                        constraints: BoxConstraints(
                      maxWidth: 170,
                  ),
                        child: Text(user.fullName,
                          maxLines:1,
                          softWrap: false,
                          overflow: TextOverflow.fade,
                          style: TextStyle(
                            color: Colors.white,
                            fontWeight: FontWeight.bold,
                            fontSize: 14,
                          ),),
                      ),
                      Text("@${user.screenName}",
                        style: TextStyle(
                          color: Colors.blueGrey,
                          fontSize: 14,
                        ),
                      )
                    ],
                  ),
                  Expanded(
                    child: Container(),
                  ),
                  Row(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: <Widget>[
                      Column(
                        crossAxisAlignment: CrossAxisAlignment.end,
                        children: <Widget>[
                          SizedBox(height: 1),
                          Text("Followed By",
                          style: TextStyle(
                            color: Colors.blueGrey,
                            fontSize: 14,
                          )),
                          Container(
                            constraints: BoxConstraints(maxWidth: 100),
                            foregroundDecoration: user.followedBy.length<2? null: BoxDecoration(
                                gradient: LinearGradient(
                                    begin: FractionalOffset.centerLeft,
                                    end: FractionalOffset.centerRight,
                                    colors: [
                                      Color(0X00121F2F),
                                      Color(0X00121F2F),
                                      Color(0XFF121F2F)
                                    ],
                                    stops: [
                                      0.0,
                                      0.7,
                                      1.0
                                    ]),
                            ),
                            child: SingleChildScrollView(
                              scrollDirection: Axis.horizontal,
                              child: Row(
                                children: <Widget>[
                                  Text(user.followedBy.join(" • "),
                                    textAlign: TextAlign.end,
                                    style: TextStyle(
                                      color: Colors.white,
                                      fontSize: 14,
                                    ),),
                                ],),
                            ),
                          ),
                        ],
                      ),
                      Padding(
                        padding: const EdgeInsets.fromLTRB(7,0,7,0),
                        child: Text("${user.followedBy.length}",
                        style: TextStyle(fontSize: 18,
                        color: Colors.white,
                        fontWeight: FontWeight.bold),),
                      ),
                    ],
                  ),
                ],
              ),
            ),
            Row(
              crossAxisAlignment: CrossAxisAlignment.baseline,
              textBaseline: TextBaseline.alphabetic,
              children: <Widget>[
                SizedBox(width: 12),
                Text(countClean(user.friendsCount),
                    style: TextStyle(color: Colors.white, fontSize: 11, fontWeight:FontWeight.w700)),
                Text(" Following",
                style: TextStyle(color: Colors.blueGrey[300], fontSize: 12)),
                SizedBox(width: 10),
                Text(countClean(user.followersCount),
                style: TextStyle(color: Colors.white, fontSize: 11, fontWeight:FontWeight.w700)),
                Text(" Followers",
                    style: TextStyle(color: Colors.blueGrey[300], fontSize: 12)),
              ],
            ),
            Visibility(
              visible: !(user.bio==''),
              child: Container(
                height: 40,
                child: Padding(
                  padding: const EdgeInsets.fromLTRB(12,0,15,0),
                  child: Row(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: <Widget>[
                      Flexible(child: Text(user.bio,
                        overflow: TextOverflow.ellipsis,
                      maxLines:2,
                      style: TextStyle(
                        color:Colors.white,
                        fontSize: 12,
                      ))),
                    ],
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class RecentHeader extends StatelessWidget {
  RecentHeader({@required this.user, @required this.verb});
  final User user;
  final String verb;
  @override
  Widget build(BuildContext context) {
    return Container(
      child: Padding(
        padding: const EdgeInsets.only(top: 10.0, bottom: 10.0),
        child: Row(
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.only(left: 18.0, right: 12),
              child: Opacity(
                opacity: 0.2,
                child: CircleAvatar(
                  backgroundImage: NetworkImage(user.img),
                  radius: 18,
                ),
              ),
            ),
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Text("${user.fullName} Recently $verb",
                  style: TextStyle(
                    color: Colors.blueGrey,
                    fontWeight: FontWeight.bold,
                  ),),
              ],
            ),
          ],
        ),
      ),
    );
  }
}

class BottomUserTile extends StatelessWidget {
  BottomUserTile({@required this.user});
  final User user;
  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(2.0),
      child: Container(
        color: Colors.blueGrey[600],
        height: user.bio==''? (user.location==''? 80 : 110) : 150,
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: <Widget>[
            Row(
              mainAxisAlignment: MainAxisAlignment.end,
              children: <Widget>[
                Padding(
                  padding: const EdgeInsets.only(right: 8.0),
                  child: InkWell(
                    child: Icon(Icons.keyboard_arrow_down,color: Colors.white,
                    ),
                    onTap: () {Navigator.pop(context);},
                  ),
                ),
              ],
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: <Widget>[
                Padding(
                  padding: const EdgeInsets.only(left: 8.0, right: 12),
                  child: CircleAvatar(
                    backgroundImage: NetworkImage(user.img),
                    radius: 18,
                  ),
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: <Widget>[
                    Text(user.fullName,
                      style: TextStyle(
                        color: Colors.white,
                        fontWeight: FontWeight.bold,
                      ),),
                    Text("@${user.screenName}",
                      style: TextStyle(
                        color: Colors.blueGrey[200],
                      ),
                    )
                  ],
                ),
                Expanded(
                  child: Container(),
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.end,
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: <Widget>[
                    Text(countClean(user.friendsCount),
                        style: TextStyle(color: Colors.white)),
                    Text(countClean(user.followersCount),
                        style: TextStyle(color: Colors.white)),
                  ],
                ),
                SizedBox(
                  width: 10,
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: <Widget>[
                    Text("Following",
                        style: TextStyle(color: Colors.blueGrey[200])),
                    Text("Followers",
                        style: TextStyle(color: Colors.blueGrey[200])),
                  ],
                ),
                SizedBox(width:12),
              ],
            ),
            SizedBox(height:10),
            Visibility(
              visible: !(user.location==''),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.start,
                children: <Widget>[
                  SizedBox(
                    width: 7,
                  ),
                  Icon(Icons.place,
                  color: Colors.blueGrey[200], size: 16),
                  Text(user.location,
                  style: TextStyle(color: Colors.blueGrey[200], fontSize:14)),
                ],
              ),
            ),
            Visibility(
              visible: !(user.bio==''),
              child: Row(
                children: <Widget>[
                  Flexible(
                    child: Padding(
                      padding: const EdgeInsets.fromLTRB(8,5,12,10),
                      child: Text(user.bio,
                          maxLines: 4,
                          overflow: TextOverflow.ellipsis,
                          style:TextStyle(
                            color: Colors.white,
                            fontSize: 13,
                          )),
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class TweetTile extends StatelessWidget {

  TweetTile({@required this.tweet});
  final Tweet tweet;

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 8.0, vertical: 4.0),
      child: Container(
        color: Color(0XFF121F2F),
        height: 115,
        child: Column(
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 2.0, vertical: 8),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: <Widget>[
                  Padding(
                    padding: const EdgeInsets.only(left: 8.0, right: 12),
                    child: CircleAvatar(
                      backgroundImage: NetworkImage(tweet.img),
                      radius: 18,
                    ),
                  ),
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: <Widget>[
                      Container(
                        constraints: BoxConstraints(
                          maxWidth: 170,
                        ),
                        child: Text(tweet.fullName,
                          maxLines:1,
                          softWrap: false,
                          overflow: TextOverflow.fade,
                          style: TextStyle(
                            color: Colors.white,
                            fontWeight: FontWeight.bold,
                          ),),
                      ),
                      Text("@${tweet.screenName}",
                        style: TextStyle(
                          color: Colors.blueGrey,
                        ),
                      )
                    ],
                  ),
                  Expanded(
                    child: Container(),
                  ),
                  Padding(
                    padding: const EdgeInsets.fromLTRB(7,0,10,0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.end,
                      children: <Widget>[
                        Row(
                          children: <Widget>[
                            Text(countClean(tweet.reTweetCount),
                                style: TextStyle(color: Colors.white, fontSize: 12, fontWeight:FontWeight.w700)),
                            Padding(
                              padding: const EdgeInsets.fromLTRB(2,0,2,0),
                              child: Icon(FontAwesomeIcons.retweet, size: 13, color: Colors.white),
                            ),
                            Visibility(
                                visible: !(tweet.favoriteCount==0),
                                child: SizedBox(width:10)
                            ),
                            Visibility(
                              visible: !(tweet.favoriteCount==0),
                              child: Text(countClean(tweet.favoriteCount),
                                  style: TextStyle(color: Colors.white, fontSize: 12, fontWeight:FontWeight.w700)),
                            ),
                            Visibility(
                              visible: !(tweet.favoriteCount==0),
                              child: Padding(
                                padding: const EdgeInsets.fromLTRB(2,0,0,0),
                                child: Icon(Icons.favorite, size: 10, color: Colors.white),
                              ),
                            ),
                          ],
                        ),
                        SizedBox(height:2),
                        Text("${tweet.createdAt}",
                          style: TextStyle(fontSize: 12,
                              color: Colors.blueGrey,
                              fontWeight: FontWeight.bold),),

                      ],
                    ),
                  ),
                ],
              ),
            ),
            Container(
              height: 50,
              child: Padding(
                padding: const EdgeInsets.fromLTRB(12,5,15,0),
                child: Row(
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: <Widget>[
                    Flexible(child: Text(tweet.tweet,
                        overflow: TextOverflow.ellipsis,
                        maxLines:3,
                        style: TextStyle(
                          color:Colors.white,
                          fontSize: 12,
                        ))),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}