import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:twittermostfollowed/components/user_tile.dart';
import 'package:twittermostfollowed/data/user_data.dart';
import 'package:twittermostfollowed/components/output_page.dart';

class LeaderScreen extends StatefulWidget {
  LeaderScreen({@required this.input});
  final UserData input;
  @override
  _LeaderScreenState createState() => _LeaderScreenState();
}

class _LeaderScreenState extends State<LeaderScreen> with SingleTickerProviderStateMixin {
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
    Tab(text: 'Leaderboard'),
    Tab(text: 'About Project'),
  ];

  @override
  Widget build(BuildContext context) {
    var tabContent = [
      LeaderTab(input: widget.input),
      AboutTab(),
    ];
    return OutputPage(
      tabList: tabList,
      tabContent: tabContent,
      tabController: controller,
      userList: widget.input.list,
      recentOn: false,
      recentCallBack: null,);
  }
}


class LeaderTab extends StatelessWidget {
  LeaderTab({@required this.input});
  final UserData input;

  @override
  Widget build(BuildContext context) {
    var users = input;
    return Container(
      color: Color(0XFF0F1926),
      child: Column(
        children: <Widget>[

          Expanded(
            child: Container(
              child: ListView.builder(
                itemBuilder: (context, i) {
                  if (i==0) {
                    return  Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: Text("Top Followed By ${users.dbUsers.length} Users in Database", style: TextStyle(color: Colors.white, fontSize: 14, fontWeight:FontWeight.bold)),
                    );
          } else {
                    return ListTile(
                      contentPadding: EdgeInsets.all(0),
                      title: FollowedTile(user: users.leadUsers[i-1]),
                    );
                  }
                  },
                itemCount: users.leadUsers.length+1,
              ),
            ),
          ),
        ],
      ),
    );
  }
}

class AboutTab extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: new BoxDecoration(
        gradient: new LinearGradient(
            colors: [
              const Color(0XFF0F1926),
              const Color(0XFF121F2F),
            ],
            begin: Alignment.bottomCenter,
            end: Alignment.topCenter,
            stops: [0.0, 1.0],
            ),
      ),

        child:
    Padding(
      padding: const EdgeInsets.all(20),
      child: Text("In looking for a way to curate my Twitter feed, finding mutual followings amongst people I admire seemed like a natural path. \n\nIn building this application, both the mobile and desktop version, I've learned a lot along the way - Not just Flutter, React, Postgres, Javascript, etc. but also how to design and engineer solutions within the constraints of multiple sequential asynchronous API calls, rate limiting, and different data formats given by the Twitter API. \n\nThanks for checking out my app. Hope you enjoyed it.",
      style: TextStyle(color: Colors.blueGrey[200], fontSize: 15, height: 1.5),),
    )
    );
  }
}

