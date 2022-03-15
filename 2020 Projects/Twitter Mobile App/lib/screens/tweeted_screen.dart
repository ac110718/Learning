import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:twittermostfollowed/components/user_tile.dart';
import 'package:twittermostfollowed/data/user_data.dart';
import 'package:twittermostfollowed/components/output_page.dart';


class TweetedScreen extends StatefulWidget {
  TweetedScreen({@required this.input});
  final UserData input;
  @override
  _TweetedScreenState createState() => _TweetedScreenState();
}

class _TweetedScreenState extends State<TweetedScreen> with SingleTickerProviderStateMixin {
  TabController controller;

  @override
  void initState() {
    super.initState();
    controller = TabController(
      length: 2,
      vsync: this,
    );
  }
  List<Tab> tabList = [
    Tab(text: 'Most Favorited'),
    Tab(text: 'Most Retweeted'),
  ];



  @override
  Widget build(BuildContext context) {
    var tabContent = [
      TweetTab(input: widget.input, rt: false),
      TweetTab(input: widget.input, rt: true),
    ];
    return OutputPage(tabList: tabList, tabContent: tabContent, tabController: controller, userList: widget.input.list, recentOn: false, recentCallBack: null,);
  }
}

class TweetTab extends StatelessWidget {

  TweetTab({@required this.input, this.rt});
  final UserData input;
  final bool rt;
  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      child: new ListView.builder(
          shrinkWrap: true,
          itemCount: rt ? input.mostTweeted.length : input.mostFavorited.length,
          itemBuilder: (context, i) {
            return TweetTile(
              tweet: rt ? input.mostTweeted[i] : input.mostFavorited[i]
            );}),);
  }
}

