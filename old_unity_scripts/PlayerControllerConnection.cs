using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlayerControllerConnection : MonoBehaviour
{
    void EstablishConnection(string ControllerId){
        Debug.Log("Establish Connection.");
        // Adds TestCharacterScript to Player
        if(ControllerId == "TestController"){
            TestCharacterScript character_script = this.gameObject.AddComponent<TestCharacterScript>();
            character_script.CharacterInitialization();
        }

        
        // Add component script to the player object for the character that the controller represents.
    }

    void UpdateGyroscope(string GyroscopeDPS){
        Debug.Log("Gyroscope update:");
        Debug.Log(GyroscopeDPS);
        var gyroscopeUpdateDPS = JsonUtility.FromJson<Vector3>(GyroscopeDPS);
    }
}
