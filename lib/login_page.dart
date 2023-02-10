import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:smart_rikshaw/authentication_service.dart';
import 'package:smart_rikshaw/dashbord.dart';

class LoginPage extends StatefulWidget {
  const LoginPage({super.key});

  @override
  State<LoginPage> createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  User? user;
  FirebaseAuth auth = FirebaseAuth.instance;

  _signInWithGoogle() async {
    await AuthenticationService.signInWithGoogle(context: context);
    if (auth.currentUser != null) {
      Navigator.pushReplacement(context,
          MaterialPageRoute(builder: (_) => Dashbord(user: auth.currentUser)));
    }
  }

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color.fromARGB(255, 248, 248, 248),
      appBar: AppBar(
        title: const Text("Login"),
        elevation: 0,
      ),
      body: Column(
        children: [
          const SizedBox(
            height: 65,
          ),
          Container(
            alignment: Alignment.center,
            child: const Image(
                height: 200,
                width: 300,
                image: NetworkImage(
                    "https://img.freepik.com/free-vector/taxi-app-concept-illustration_52683-36028.jpg?w=1380&t=st=1670410588~exp=1670411188~hmac=3d3f0dc4c31979648b1811857a0b60572f16d99417d02d0f941ed72d50c9ffa3")),
          ),
          const Spacer(),

          ClipRRect(
            borderRadius: BorderRadius.circular(30),
            child: ElevatedButton(
                onPressed: _signInWithGoogle,
                child: const Padding(
                  padding: EdgeInsets.all(20.0),
                  child: Text(
                    "Sign in with Google",
                  ),
                )),
          ),
          const SizedBox(
            height: 50,
          )
          // Image(image: Image.network("https://img.freepik.com/free-vector/taxi-app-concept-illustration_52683-36028.jpg?w=1380&t=st=1670410588~exp=1670411188~hmac=3d3f0dc4c31979648b1811857a0b60572f16d99417d02d0f941ed72d50c9ffa3")),
        ],
      ),
    );
  }
}
