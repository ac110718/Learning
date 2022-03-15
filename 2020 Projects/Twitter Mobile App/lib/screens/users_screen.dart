import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';
import 'package:twittermostfollowed/data/user_data.dart';
import 'package:twittermostfollowed/data/user.dart';
import 'package:twittermostfollowed/components/user_tile.dart';
import 'dart:async';

class UserScreen extends StatefulWidget {
  UserScreen({this.processFunction});
  final Function processFunction;
  @override
  _UserScreenState createState() => _UserScreenState();
}






class _UserScreenState extends State<UserScreen> {


  String reqUser;
  String status;
  List<User> usersOut = [];
  final input = TextEditingController();
  bool loading = false;
  String loadString = '';

  void add() async {
    var response = await users.addUser(reqUser);
    if (response[0]) {
      setState(() {usersOut = response[2];});
    }
    setState(() {
      status = response[1];
      final snackBar = SnackBar(content: Text(status, style:TextStyle(color: Colors.white)), backgroundColor: Color(0X330F1926));
      Scaffold.of(context).showSnackBar(snackBar);
    });
    input.clear();
  }
  UserData users = UserData();

  void addDB (dbuser) {
    users.addDBUSer(dbuser);
    setState(() {usersOut = users.list;});
  }


  void delete (user) {
    setState(() {
      usersOut = users.deleteUser(user);
    });
  }

  var countLead=0;

  statusTimer() {
    Timer.periodic(Duration(seconds: 1), (timer) {
      if (!loading) {
        timer.cancel();
      }
      setState(() {
        loadString = users.status;
      });
    });
  }
  void analyze() async {
    setState(() {
      loading = true;
    });
    statusTimer();
    var response = await users.processData();

    if (countLead==0) {
      await users.getLeader();
    }
      setState((){
        status = response;
        final snackBar = SnackBar(content: Text(status, style:TextStyle(color: Colors.white)), backgroundColor: Color(0X330F1926));
        Scaffold.of(context).showSnackBar(snackBar);
        loading = false;
        countLead++;
      });
      widget.processFunction(users);

  }

  var dbCount = 0;

 showDB() async {

    if (dbCount==0) {
      setState(() {
        loading = true;
      });
      statusTimer();
      var response = await users.getDataBase();

      setState(() {
        dbCount++;
        loading = response ? false : true;
      });
    }

    showModalBottomSheet(
      context: context,
      isScrollControlled: true,
      isDismissible: true,
      backgroundColor: Colors.transparent,
      builder: (context) =>
          DraggableScrollableSheet(
            initialChildSize: 0.5,
            minChildSize: 0.2,
            maxChildSize: 0.8,
            builder: (context, scrollController) {
              return Container(
                color: Color(0XCC121F2F),
                child: Padding(
                  padding: const EdgeInsets.only(top:10),
                  child: ListView.builder(
                    controller: scrollController,
                    itemBuilder: (context, i) {
                      if (i==0) {
                        return Padding(
                          padding: const EdgeInsets.all(10.0),
                          child: Column(
                            crossAxisAlignment: CrossAxisAlignment.start,
                            children: <Widget>[
                              Row(
                                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                                children: <Widget>[
                                  Text("Previously Searched Users", style: TextStyle(color: Colors.white, fontSize: 13, fontWeight: FontWeight.w600)),
                                  Padding(
                                    padding: const EdgeInsets.only(right: 10.0),
                                    child: Row(
                                      children: <Widget>[
                                        Text("${users.dbUsers.length}", style: TextStyle(color:Colors.blueGrey[700], fontSize:12, fontWeight: FontWeight.w900)),
                                        SizedBox(width:5),
                                        Icon(Icons.group, color:Colors.blueGrey[700])
                                      ],
                                    ),
                                  ),
                                ],
                              ),
                              Text("Loaded on PostgreSQL Database", style: TextStyle(color:Colors.blueGrey[400], fontSize:13)),
                            ],
                          ),
                        );
                      } else {
                        return Padding(
                          padding: const EdgeInsets.symmetric(horizontal: 8.0, vertical: 2),
                          child: DBTile(user: users.dbUsers[i-1], added: usersOut.map((x)=>x.screenName).contains(users.dbUsers[i-1].screenName), addFunction: addDB,),
                        );
                      }
                    },
                    itemCount: users.dbUsers.length+1,
                  ),
                ),
              );
            },
          ),
    );
  }


  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      child: SafeArea(
        child: Stack(
          children: <Widget>[
            Column(
            mainAxisAlignment: MainAxisAlignment.start,
            children: <Widget>[
              new SizedBox(height: 10),
              Padding(
                padding: const EdgeInsets.all(10.0),
                child: new TextField(
                  textAlignVertical: TextAlignVertical.center,
                  textAlign: TextAlign.left,
                  controller: input,
                  textInputAction: TextInputAction.go,
                  onSubmitted: (value) {add();},
                  onChanged:  (newText) {reqUser = newText;},
                  style: TextStyle(
                    fontSize: 14.0,
                    color: Colors.white,
                  ),
                  decoration: InputDecoration(
                    enabledBorder: OutlineInputBorder(
                      borderSide: BorderSide(
                        color: Colors.blueGrey,
                        width:1,),
                      borderRadius: BorderRadius.circular(10),
                    ),
                    focusedBorder: OutlineInputBorder(
                      borderSide: BorderSide(
                        color: Colors.white,
                        width: 2,
                      ),
                      borderRadius: BorderRadius.circular(10),
                    ),
                    alignLabelWithHint: true,
                    hintText: 'Enter Twitter Screen Name',
                    hintStyle: TextStyle(
                      color: Color(0XAAFFFFFF),
                    ),
                    prefixIcon: Icon(Icons.keyboard_arrow_right, color: Colors.white, size: 28),
                    suffixIcon: InkWell(
                      child: Padding(
                        padding: EdgeInsets.only(right: 10.0),
                        child: Icon(FontAwesomeIcons.searchPlus, size: 17, color: Colors.white),
                      ),
                      onTap: add,
                    ),
                  ),
                ),
              ),
              Padding(
                padding: const EdgeInsets.all(0),
                child: SizedBox(
                  width: double.infinity,
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    children: <Widget>[
                      Padding(
                        padding: const EdgeInsets.only(left: 15.0),
                        child: InkWell(
                            child: Row(
                              mainAxisAlignment: MainAxisAlignment.start,
                              children: <Widget>[
                                Icon(FontAwesomeIcons.database, color: Colors.blueGrey[200], size: 12),
                                SizedBox(width:5),
                                Text("Load Database", style: TextStyle(color: loading? Colors.white : Colors.blueGrey[200],  fontWeight: FontWeight.bold,)),
                              ],
                            ),
                            onTap: () => showDB()
                        ),
                      ),
                      FlatButton(
                        padding: EdgeInsets.only(right:15),
                        color: Color(0XFF0F1926),
                        child: Row(
                          mainAxisAlignment: MainAxisAlignment.end,

                          children: <Widget>[
                            new Text("Analyze Users",
                              style: TextStyle(
                                color: loading? Colors.white : Colors.blue[300],
                                fontWeight: FontWeight.bold,
                              ),),

                            Padding(
                              padding: const EdgeInsets.only(right: 0.0, left: 20, top: 10, bottom: 10),
                              child: new Icon(FontAwesomeIcons.twitter, color: Colors.blueAccent),
                            ),
                          ],
                        ),
                        onPressed: (usersOut.length==0 || loading)? null : () {analyze();},
                      ),
                    ],
                  ),
                ),
              ),
              new Expanded(
                child: new ListView.builder(
                    shrinkWrap: true,
                    itemCount: usersOut.length,
                    itemBuilder: (context, i) {
                      return UserTile(
                          user: usersOut[i],
                          delFunction: () {delete(usersOut[i]);}
                      );
                    }
                ),
              ),
            ],
          ),
            Visibility(
              visible: loading,
              child: Center(
                child: Container(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: <Widget>[
                      CircularProgressIndicator(strokeWidth:5, backgroundColor: Color(0X00121F2F), valueColor: new AlwaysStoppedAnimation<Color>(Color(0XFF122F3F))),
                      SizedBox(height:10),
                      Text("Loading $loadString...", style: TextStyle(color: Colors.blueGrey,fontSize:12,fontWeight:FontWeight.bold)),
                    ],
                  ),
                  width:double.infinity,
                  height:double.infinity,
                  color: Color(0X88122F3F),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

