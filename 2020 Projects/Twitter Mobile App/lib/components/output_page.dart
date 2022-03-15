import 'package:flutter/material.dart';
import 'package:twittermostfollowed/data/user.dart';
import 'package:twittermostfollowed/components/user_carousel.dart';


class OutputPage extends StatelessWidget {

  OutputPage({@required this.tabList, @required this.tabContent, @required this.tabController, @required this.userList, this.recentOn, this.recentCallBack});
  final List<Tab> tabList;
  final List<Widget> tabContent;
  final TabController tabController;
  final List<User> userList;
  final Function recentCallBack;
  final bool recentOn;

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        Navigator.maybePop(context);
        FocusScopeNode currentFocus = FocusScope.of(context);
        if (!currentFocus.hasPrimaryFocus) {
          currentFocus.unfocus();
        }
      },
      child: CustomScrollView(
          slivers: <Widget>[
            SliverAppBar(
              automaticallyImplyLeading: false,
              primary: true,
              expandedHeight: 90.0,
              floating: true,
              pinned: true,
              snap: true,
              elevation: 5,
              backgroundColor: Color(0XFF0F1926),
              flexibleSpace: FlexibleSpaceBar(
                background: UserCarousel(userList: userList, custom: recentOn, callback: recentCallBack),
              ),
              bottom: PreferredSize(
                preferredSize: Size.fromHeight(50.0),
                child: Align(
                  alignment: Alignment.bottomLeft,
                  child: TabBar(
                    tabs: tabList,
                    labelColor: Colors.white,
                    unselectedLabelColor: Colors.blueGrey,
                    controller: tabController,
                    isScrollable: true,
                    indicator: UnderlineTabIndicator(
                        borderSide: BorderSide(width: 4.0, color: Colors.white),
                        insets: EdgeInsets.symmetric(horizontal:16.0)
                    ),
                  ),
                ),
              ),
            ),
            SliverFillRemaining(
              child: TabBarView(
                controller: tabController,
                children: tabContent,
              ),
            ),
          ]
      ),
    );
  }
}






