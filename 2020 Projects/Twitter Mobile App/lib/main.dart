import 'package:flutter/material.dart';
import 'package:twittermostfollowed/screens/users_screen.dart';
import 'package:twittermostfollowed/screens/followed_screen.dart';
import 'package:twittermostfollowed/screens/tweeted_screen.dart';
import 'package:twittermostfollowed/screens/liked_screen.dart';
import 'package:twittermostfollowed/screens/login_screen.dart';
import 'package:twittermostfollowed/screens/leader_screen.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';


void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.


  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Twitter Filter',
      theme: new ThemeData(

        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'Twitter Filter'),
      );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => new _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {


  bool hasProcessed = false;
  bool loggedIn = false;

  int _selectedIndex = 0;

  List<Widget> pageList = List<Widget>();

  void login() {
    setState(() {
      loggedIn = true;
    });
  }

  void process(users) {
    if (hasProcessed) {
      setState(() {
        pageList = [pageList[0]];
      });
    } else {
      setState(() {
        hasProcessed = true;
      });
    }
    pageList.add(FollowedScreen(input: users));
    pageList.add(TweetedScreen(input: users));
    pageList.add(LikedScreen(input: users));
    pageList.add(LeaderScreen(input: users));
  }

  void _onItemTapped(int index) {
    if (hasProcessed) {
      setState(() {
        _selectedIndex = index;
      });
    }
  }


  @override
  void initState() {
    pageList.add(UserScreen(processFunction: process));
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        FocusScopeNode currentFocus = FocusScope.of(context);
        if (!currentFocus.hasPrimaryFocus) {
          currentFocus.unfocus();
        }},
      child: Scaffold(
        body: !loggedIn? LoginScreen(authFunction: login) :
        Center(
            child: IndexedStack(
              index: _selectedIndex,
              children: pageList,
            ),
        ),
        bottomNavigationBar: BottomNavigationBar(
          type: BottomNavigationBarType.fixed,
          backgroundColor: Color(0XFF0F1926),
          items: const <BottomNavigationBarItem>[
            BottomNavigationBarItem(
              icon: Icon(FontAwesomeIcons.searchPlus, size: 18),
              title: Text('Users'),
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.person_add),
              title: Text('Followed'),
            ),
            BottomNavigationBarItem(
              icon: Icon(FontAwesomeIcons.twitter),
              title: Text('Tweeted'),
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.favorite),
              title: Text('Liked'),
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.format_list_bulleted),
              title: Text('Leader'),
            ),
          ],
          currentIndex: _selectedIndex,
          selectedItemColor: Colors.white,
          selectedFontSize: 12.0,
          unselectedItemColor: hasProcessed ? Colors.blueGrey : Color(0XFF121F2F),
          showUnselectedLabels: true,
          unselectedLabelStyle: TextStyle(color: hasProcessed ? Colors.white : Colors.blueGrey),
          onTap: _onItemTapped,
        ),
      ),
    );
  }
}


