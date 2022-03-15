import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:twittermostfollowed/data/user.dart';
import 'package:twittermostfollowed/data/user_data.dart';
import 'package:twittermostfollowed/components/user_tile.dart';
import 'package:twittermostfollowed/components/output_page.dart';


class LikedScreen extends StatefulWidget {
  LikedScreen({@required this.input});
  final UserData input;
  @override
  _LikedScreenState createState() => _LikedScreenState();
}

class _LikedScreenState extends State<LikedScreen> with SingleTickerProviderStateMixin {
  
  TabController controller;

  @override
  void initState() {
    super.initState();
    controller = TabController(
      length: 2,
      vsync: this,
    );
    controller.addListener(handleTabSelection);
  }

  bool recentOn = true;

  void handleTabSelection () {
    var setting = controller.index ==0? true: false;
    setState(() {
      recentOn = setting;
    });
  }


  @override
  Widget build(BuildContext context) {

    List<double> getHeight() {
      double header = 50;
      double tileHeight = 125;
      double count = 0;
      List<double> list = [];

      for (var item in widget.input.mostRecentlyLiked) {
        list.add(count);
        count += (header + tileHeight * item[1].length);
      }
      return list;
    }

    final byUserController = new ScrollController();

    List<double> scrollHeight = getHeight();
    void carouselOnTap(index) {
      byUserController.animateTo(scrollHeight[index], duration: new Duration(seconds: 1), curve: Curves.ease);
    }

    List<Tab> tabList = [
      Tab(text: 'Recent Likes'),
      Tab(text: 'Most Liked'),
    ];
    var tabContent = [
      RecentlyLiked(input: widget.input, controller: byUserController),
      TweetTab(input: widget.input),
    ];
    return OutputPage(tabList: tabList, tabContent: tabContent, tabController: controller, userList: widget.input.list, recentOn: recentOn, recentCallBack: carouselOnTap);
  }
}

class TweetTab extends StatelessWidget {
  TweetTab({@required this.input});
  final UserData input;
  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      child: new ListView.builder(
          shrinkWrap: true,
          itemCount: input.mostLiked.length,
          itemBuilder: (context, i) {
            return TweetTile(
              tweet: input.mostLiked[i],
            );}),);
  }
}

class RecentlyLiked extends StatefulWidget {
  RecentlyLiked({@required this.input, this.controller});
  final UserData input;
  final ScrollController controller;

  @override
  _RecentlyLikedState createState() => _RecentlyLikedState();
}

class _RecentlyLikedState extends State<RecentlyLiked> {

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      child: ListView.builder(
          controller: widget.controller,
          shrinkWrap: true,
          scrollDirection: Axis.vertical,
          itemCount: widget.input.mostRecentlyLiked.length,
          itemBuilder: (context, i) {return RecentLikeTile(
            user: widget.input.mostRecentlyLiked[i][0],
            recentlyLiked: widget.input.mostRecentlyLiked[i][1],
          );}
      ),
    );
  }
}

class RecentLikeTile extends StatelessWidget {
  RecentLikeTile({@required this.user, @required this.recentlyLiked});
  final User user;
  final List recentlyLiked;

  List<Widget> recentGen(User userInput, List recentInput) {
    final List<Widget> list = [];
    list.add(RecentHeader(user: userInput, verb: "Liked"));
    for (Tweet recentLike in recentInput) {
      list.add(TweetTile(tweet: recentLike));
    }
    return list;
  }

  @override
  Widget build(BuildContext context) {
    return Column(
        children: recentGen(user, recentlyLiked)
    );
  }
}

