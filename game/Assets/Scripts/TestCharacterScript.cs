using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestCharacterScript : MonoBehaviour
{
    PlayerState state;

    public void CharacterInitialization()
    {
        state = GetComponent<PlayerState>();
    }

    // Update is called once per frame
    void UpdateCharacterFromGyroscope(string GyroscopeDPS)
    {
        // transform.position = transform.position + new Vector3(0.01f,0,0); 
        Debug.Log("Gyroscope update:");
        Debug.Log(GyroscopeDPS);
        var gyroscopeUpdateDPS = JsonUtility.FromJson<Vector3>(GyroscopeDPS);
        state.move = new Vector2(gyroscopeUpdateDPS[0],state.move.y);
    }
}
