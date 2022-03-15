import 'package:flutter/foundation.dart';

class User {
  User({@required this.screenName, this.fullName, this.bio, this.friendsCount, this.followersCount, this.img, this.location, this.id, this.followedBy});
  final String screenName;
  final String fullName;
  final String bio;
  final int friendsCount;
  final int followersCount;
  final String img;
  final String location;
  final String id;
  final List followedBy;
}


class Tweet {
  Tweet({@required this.screenName, this.createdAt, this.fullName, this.tweet, this.reTweetCount, this.favoriteCount, this.img, this.twitid, this.id, this.favoritedBy});
  final String screenName;
  final String fullName;
  final String tweet;
  final int reTweetCount;
  final int favoriteCount;
  final String img;
  final String twitid;
  final String id;
  final List favoritedBy;
  final String createdAt;
}