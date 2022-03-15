import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:twittermostfollowed/data/user.dart';
import 'package:twittermostfollowed/data/user_data.dart';
import 'package:twittermostfollowed/components/user_tile.dart';
import 'package:twittermostfollowed/components/output_page.dart';


class FollowedScreen extends StatefulWidget {
  FollowedScreen({@required this.input});
  final UserData input;

  @override
  _FollowedScreenState createState() => _FollowedScreenState();
}

class _FollowedScreenState extends State<FollowedScreen> with SingleTickerProviderStateMixin {



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

  bool recentOn = false;

  void handleTabSelection () {
    var setting = controller.index ==1? true: false;
      setState(() {
        recentOn = setting;
      });
  }

  List<Tab> tabList = [
    Tab(text: 'Most Followed'),
    Tab(text: 'Recent Followings'),
  ];

  @override
  Widget build(BuildContext context) {

    List<double> getHeight() {
      double header = 50;
      double woBio = 90;
      double wBio = 125;
      double count = 0;
      List<double> list = [];

      for (List item in widget.input.mostRecentlyFollowed) {
        list.add(count);
        count += header;
        for (User recUser in item[1]) {
          double rowHeight = recUser.bio==''? woBio:wBio;
          count += rowHeight;
        }
      }
      return list;
    }

    final byUserController = new ScrollController();

    List<double> scrollHeight = getHeight();
    void carouselOnTap(index) {
      byUserController.animateTo(scrollHeight[index], duration: new Duration(seconds: 1), curve: Curves.ease);
    }

    var tabContent = [
      MostFollowed(input: widget.input),
      RecentlyFollowed(input: widget.input, controller: byUserController)
    ];

    return OutputPage(tabList: tabList, tabContent: tabContent, tabController: controller, userList: widget.input.list, recentOn: recentOn, recentCallBack: carouselOnTap);
  }
}

class MostFollowed extends StatelessWidget {
  MostFollowed({@required this.input});
  final UserData input;
  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      child: new ListView.builder(
          shrinkWrap: true,
          itemCount: input.mostFollowed.length,
          itemBuilder: (context, i) {
            return FollowedTile(
              user: input.mostFollowed[i],
            );}),);
  }
}

class RecentlyFollowed extends StatefulWidget {
  RecentlyFollowed({@required this.input, this.controller});
  final UserData input;
  final ScrollController controller;

    @override
  _RecentlyFollowedState createState() => _RecentlyFollowedState();
}

class _RecentlyFollowedState extends State<RecentlyFollowed> {

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      child: ListView.builder(
        controller: widget.controller,
        shrinkWrap: true,
        scrollDirection: Axis.vertical,
        itemCount: widget.input.mostRecentlyFollowed.length,
        itemBuilder: (context, i) {return RecentTile(
            user: widget.input.mostRecentlyFollowed[i][0],
          recentlyFollowed: widget.input.mostRecentlyFollowed[i][1],
        );}
      ),
    );
  }
}

class RecentTile extends StatelessWidget {
  RecentTile({@required this.user, @required this.recentlyFollowed});
  final User user;
  final List recentlyFollowed;

  List<Widget> recentGen(User userInput, List recentInput) {
    final List<Widget> list = [];
    list.add(RecentHeader(user: userInput, verb: "Followed"));
    for (User recentUser in recentInput) {
      list.add(FollowedTile(user: recentUser));
    }
    return list;
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      children: recentGen(user, recentlyFollowed)
    );
  }
}






