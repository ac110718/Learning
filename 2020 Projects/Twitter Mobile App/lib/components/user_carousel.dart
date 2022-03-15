import 'package:flutter/material.dart';
import 'package:twittermostfollowed/data/user.dart';
import 'package:twittermostfollowed/components/user_tile.dart';

class UserCarousel extends StatelessWidget {
  UserCarousel({@required this.userList, this.custom, this.callback});
  final List<User> userList;
  final bool custom;
  final Function callback;

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Color(0XFF0F1926),
      child: ListView.builder(
        shrinkWrap: true,
            scrollDirection: Axis.horizontal,
            itemCount: userList.length,
            itemBuilder: (BuildContext context, int index) {
              return FlatButton(
                padding: EdgeInsets.fromLTRB(2,2,2,20),
                child: Container(
                  color: Color(0XFF121F2F),
                  child: Padding(
                    padding: const EdgeInsets.symmetric(horizontal:10, vertical: 5),
                    child: Row(
                      children: <Widget>[
                          CircleAvatar(
                          backgroundImage: NetworkImage(userList[index].img),
                          radius: 10,
                        ),
                        SizedBox(width: 8),
                        Text(userList[index].fullName,
                        style: TextStyle(
                          color: Colors.grey[350],
                          fontSize: 12,
                        )),
                      ],
                    ),
                  ),
                ),
                onPressed: () {
                  custom? callback(index) :
                  showBottomSheet(
                      context: context,
                      builder: (context) => BottomUserTile(user: userList[index]));
                } ,
              );
            }
          ),
    );
  }
}



