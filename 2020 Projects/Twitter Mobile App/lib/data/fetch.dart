import 'package:http/http.dart' as http;
import 'dart:convert';
import 'package:flutter/foundation.dart';

class Fetch {
  Fetch({@required this.url, @required this.json});
  final String url;
  final Object json;
  Future<dynamic> getData() async {
    http.Response response = await http.post(
      'https://smart-tweet.herokuapp.com/$url',
      headers: <String, String>{'Content-Type': 'application/json; charset=UTF-8',},
      body: jsonEncode(json),
    );
    return jsonDecode(response.body);
  }
}

