import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:smart_rikshaw/authentication_service.dart';
import 'package:smart_rikshaw/gmap_screen.dart';

import 'login_page.dart';

class Dashbord extends StatefulWidget {
  Dashbord({super.key, required this.user});
  User? user;
  @override
  State<Dashbord> createState() => _DashbordState();
}

class _DashbordState extends State<Dashbord> {
  final DatabaseReference databaseRef = FirebaseDatabase.instance.ref();
  FirebaseAuth auth = FirebaseAuth.instance;

  init() {
    databaseRef.child("EV1").once().then((snapshot) {
      print('Data : ${snapshot.snapshot.value}');
      print(widget.user);
    });
  }

  @override
  void initState() {
    init();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Dashbord"),
        elevation: 0,
        actions: [
          IconButton(
              onPressed: () {
                AuthenticationService.signOut(context: context).then((value) =>
                    Navigator.pushReplacement(context,
                        MaterialPageRoute(builder: (_) => const LoginPage())));
              },
              icon: const Icon(Icons.logout))
        ],
      ),
      body: Column(
        children: [
          SizedBox(
            height: 20,
          ),
          Container(
            alignment: Alignment.centerLeft,
            margin: const EdgeInsets.only(left: 25),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      'Hello Harsh',
                      // 'Hello, ${widget.user!.displayName.toString().split(' ')[0]}',
                      style:
                          TextStyle(fontSize: 25, fontWeight: FontWeight.w600),
                    ),
                    Text(
                      'Here All Devices Work Smartly.',
                      style: TextStyle(fontSize: 16),
                    ),
                  ],
                ),
                Padding(
                  padding: const EdgeInsets.all(15.0),
                  child: Tooltip(
                    message: 'Show Status of Device',
                    child: Icon(
                      Icons.circle,
                      color: 0 == 0 ? Colors.red : Colors.green,
                      size: 19,
                    ),
                  ),
                )
              ],
            ),
          ),
          SizedBox(
            height: 20,
          ),
          Container(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                Row(
                  children: [
                    Image(
                        height: 47,
                        image: NetworkImage(
                            "https://cdn-icons-png.flaticon.com/512/1247/1247137.png?w=826&t=st=1670420193~exp=1670420793~hmac=a22142e58853755086fe2c12f02a25dd4ea4f3a419739e00b23494ddfd1b19b3")),
                    Column(
                      children: [
                        Text(
                          '25°C',
                          style: TextStyle(
                            fontSize: 22,
                            fontWeight: FontWeight.w600,
                          ),
                        ),
                        Text('Temperature')
                      ],
                    )
                  ],
                ),
                Row(
                  children: [
                    Image(
                      height: 47,
                      image: NetworkImage(
                          'https://cdn-icons-png.flaticon.com/512/1163/1163648.png?w=826&t=st=1670420449~exp=1670421049~hmac=fc2e618f438dc59afa9b1474ca29ffe8e6c764709f53bbcd840d2585afdcc05b'),
                    ),
                    Column(
                      children: [
                        Text(
                          '75%',
                          style: TextStyle(
                            fontSize: 22,
                            fontWeight: FontWeight.w600,
                          ),
                        ),
                        Text('Humidity')
                      ],
                    ),
                  ],
                )
              ],
            ),
          ),
          Spacer(),
          Container(
            height: MediaQuery.of(context).size.height * 0.55,
            child: ListView(
              physics: BouncingScrollPhysics(
                  parent: AlwaysScrollableScrollPhysics()),
              padding: const EdgeInsets.all(8.0),
              shrinkWrap: false,
              scrollDirection: Axis.horizontal,
              children: [
                cardUI(
                    NetworkImage(
                        "https://img.freepik.com/free-vector/monitor-size_53876-26769.jpg?w=826&t=st=1670419834~exp=1670420434~hmac=8fa160cb4ed8f9e973a0cc0cd4aee2109d50ef54f10270ed339f03eeb0873316"),
                    'THERMALS',
                    context),
                cardUI(
                    NetworkImage(
                        "https://img.freepik.com/free-vector/flat-design-indian-man-driving-van_23-2149757883.jpg?w=826&t=st=1670420062~exp=1670420662~hmac=afbfc69fbec1c3f59c767bcec0cc06650feea61b06b9ee511dc752e60fdcaa83"),
                    'SEATS',
                    context),
                cardUI(
                    NetworkImage(
                        "https://img.freepik.com/free-vector/gps-navigation-illustration_24877-57123.jpg?w=826&t=st=1670420130~exp=1670420730~hmac=d8a6e1f206268f9e56422a6476cc61e220c034a356bed8cacf03e2868ebb181d"),
                    'GPS NAVIGATION',
                    context),
              ],
            ),
          ),
          Spacer()
        ],
      ),
    );
  }

  Widget cardUI(ImageProvider imgUrl, String roomName, BuildContext context) {
    return InkWell(
      splashColor: Colors.blue,
      onTap: () {
        // if (roomName == 'THERMALS') {
        //   Navigator.pushNamed(context, 'bedroom-screen');
        // } else if (roomName == 'SEATS') {
        //   Navigator.pushNamed(context, 'bedroom-screen');
        // }
        if (roomName == 'GPS NAVIGATION') {
          Navigator.of(context).push(MaterialPageRoute(
              builder: (context) => GmapScreen("27.6056887", "77.5911358")));
        }
      },
      child: Container(
        margin: const EdgeInsets.only(right: 10),
        width: MediaQuery.of(context).size.width * 0.75,
        child: Card(
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(15),
          ),
          elevation: 8,
          child: Stack(fit: StackFit.expand, children: [
            ClipRRect(
              borderRadius: BorderRadius.circular(15),
              child: Image(
                image: imgUrl,
                fit: BoxFit.cover,
              ),
            ),
            Container(
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(15),
                color: Colors.black45,
              ),
              alignment: Alignment.center,
              child: Text(
                roomName,
                style: TextStyle(
                  color: Colors.white,
                  letterSpacing: 1.5,
                  fontSize: 24,
                  fontWeight: FontWeight.w600,
                ),
                textAlign: TextAlign.center,
              ),
            )
          ]),
        ),
      ),
    );
  }
}
