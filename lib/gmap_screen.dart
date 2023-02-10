import 'dart:io';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:webview_flutter/webview_flutter.dart';

// ignore: must_be_immutable
class GmapScreen extends StatefulWidget {
  String lat;
  String lon;
  GmapScreen(this.lat, this.lon, {Key? key}) : super(key: key);

  @override
  State<GmapScreen> createState() => _GmapScreenState();
}

class _GmapScreenState extends State<GmapScreen> {
  @override
  void initState() {
    if (Platform.isAndroid) WebView.platform = AndroidWebView();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    // valueListener();

    return Scaffold(
      appBar: AppBar(
        // Here we take the value from the MyHomePage object that was created by
        // the App.build method, and use it to set our appbar title.
        title: const Text("Map"),
      ),

      body: WebView(
        javascriptMode: JavascriptMode.unrestricted,
        initialUrl:
            'https://www.google.com/maps?q=${widget.lat},${widget.lon}&z=17&hl=en',
      ),
      // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}

// 27.6112905 lat
//77.5963159 lon
