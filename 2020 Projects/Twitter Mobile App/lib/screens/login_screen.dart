import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:twittermostfollowed/data/fetch.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';

class LoginScreen extends StatefulWidget {
  LoginScreen({this.authFunction});
  final Function authFunction;
  @override
  _LoginScreenState createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {

  final input = TextEditingController();
  String password;

  void authenticate() async {
    var fetch = new Fetch(url: 'login', json: {'pw':password});
    var response = await fetch.getData();
    print(response);
    if (response['auth']) {
      widget.authFunction();
    } else {
      final snackBar = SnackBar(content: Text("Sorry, wrong password.", style:TextStyle(color: Colors.white)), backgroundColor: Color(0X330F1926));
      Scaffold.of(context).showSnackBar(snackBar);
    }
  }


  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      height: double.infinity,
      width: double.infinity,
      child: SafeArea(
        child: Padding(
                padding: const EdgeInsets.all(10.0),
                child: Column(
                  children: <Widget>[
                    SizedBox(height:150),

                    TextField(
                      obscureText: true,
                      textAlignVertical: TextAlignVertical.center,
                      textAlign: TextAlign.left,
                      controller: input,
                      textInputAction: TextInputAction.go,
                      onSubmitted: (value) {authenticate();},
                      onChanged:  (newText) {password = newText;},
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
                        hintText: 'Welcome. Please Enter Password.',
                        hintStyle: TextStyle(
                          color: Color(0XAAFFFFFF),
                        ),
                        prefixIcon: Icon(Icons.keyboard_arrow_right, color: Colors.white, size: 28),
                        suffixIcon: InkWell(
                          child: Padding(
                            padding: EdgeInsets.only(right: 10.0),
                            child: Icon(FontAwesomeIcons.twitter, size: 17, color: Colors.blueAccent),
                          ),
                          onTap: authenticate,
                        ),
                      ),
                    ),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.start,
                      children: <Widget>[
                        Expanded(
                          flex: 4,
                          child: Padding(
                            padding: const EdgeInsets.fromLTRB(10,30,70,0),
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: <Widget>[
                                Text("Who Are The Smart People Following \non Twitter ?",
                                    style: TextStyle(color:Colors.white, fontSize: 16, fontWeight: FontWeight.w700)),
                                SizedBox(height:15),
                                Text("Find mutual and recent followings, and \nmost re-tweeted posts.",
                                    style: TextStyle(color:Colors.blueGrey, fontSize: 14, fontWeight: FontWeight.w300)),
                              ],
                            ),
                          ),
                        ),
                      ],
                    ),

                  ],
                ),
              ),
    ));
  }
}

