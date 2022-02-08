using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlayerControllerConnection : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    void Update(){

    }

    void EstablishConnection(string ControllerId){
        Debug.Log("Establish Connection.");
        // Adds TestCharacterScript to Player
        if(ControllerId == "TestController"){
            this.gameObject.AddComponent<TestCharacterScript>();
        }
        
        // Add component script to the player object for the character that the controller represents.
    }

    void UpdateGyroscope(string GyroscopeDPS){
        Debug.Log("Gyroscope update:");
        Debug.Log(GyroscopeDPS);
        var gyroscopeUpdateDPS = JsonUtility.FromJson<Vector3>(GyroscopeDPS);
    }
}
