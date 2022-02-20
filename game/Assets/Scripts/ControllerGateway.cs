using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct Player
{
    public Vector2 startingPosition;
    public string controllerId;
    public string playerId;
    public BLEState characterBLEState;
};

public struct ControllerConnectionInfo
{
    public string controllerId;
    public string playerId;
};

public struct SensorXYZInfo
{
    public float x;
    public float y;
    public float z;
    public string playerId;
};

public class ControllerGateway : MonoBehaviour
{
    //Could be a List instead of a dictionary? List<Player> Players = new List<Player>();
    public Dictionary<string, Player> Players = new Dictionary<string, Player>();
    // Start is called before the first frame update

    void Start()
    {
        // ControllerConnection("{\"playerId\":\"Player1\",\"controllerId\":\"TestController\"}");
    }

    void ControllerConnection(string jsConnectionInfo)
    {
        /* 
            Method called from javascript when the connection is established with teh controller.
            Input:
                - jsConnectionInfo: string({"controllerId":"ABC1234", "playerId":"Player1"})
            Does:
                Loads the appropiate character associated to the corresponding player.

                Instantiates the character. (TODO: Move this to another method.)
        */
        ControllerConnectionInfo connectionInfo = JsonUtility.FromJson<ControllerConnectionInfo>(jsConnectionInfo);
        // TODO: 
        string CharacterPrefabPath = "";
        switch (connectionInfo.controllerId)
        {
            case "TestController":
                CharacterPrefabPath = "CharacterPrefabs/TSTCharacter";
                break;
            default:
                // return;
                break;
        }
        // if(connectionInfo.controllerId == "TestController"){
        //     Players[connectionInfo.playerId].Character = Resources.Load("CharacterPrefabs/TSTCharacter");
        // }  
        Player newPlayer = new Player();
        Object characterPrefab = Resources.Load(CharacterPrefabPath);
        newPlayer.controllerId = connectionInfo.controllerId;
        newPlayer.playerId = connectionInfo.playerId;
        newPlayer.startingPosition = getPlayerStartingPosition(connectionInfo.playerId);
        newPlayer.characterBLEState = Instantiate(characterPrefab, newPlayer.startingPosition, Quaternion.identity) as BLEState;
        //newPlayer.state = newPlayer.Character.GetComponent<TSTState>;
        Players[connectionInfo.playerId] = newPlayer;
    }

    Vector2 getPlayerStartingPosition(string playerId)
    {
        /*
            Returns a default starting position for each player.
        */
        Vector2 startingPosition;
        switch (playerId)
        {
            case "Player1":
                startingPosition = new Vector2(-3, 0);
                break;
            case "Player2":
                startingPosition = new Vector2(3, 0);
                break;
            default:
                startingPosition = new Vector2(0, 0);
                break;
        }
        return startingPosition;
    }

    void UpdateGyroscope(string GyroscopeInfo)
    {
        Debug.Log("ControllerGateway.UpdateGyroscope");
        SensorXYZInfo gyroscopeUpdateInfo = JsonUtility.FromJson<SensorXYZInfo>(GyroscopeInfo);
        Vector3 gyroscopeDPS = new Vector3(gyroscopeUpdateInfo.x, gyroscopeUpdateInfo.y, gyroscopeUpdateInfo.z);
        Players[gyroscopeUpdateInfo.playerId].characterBLEState.GyroscopeToState(gyroscopeDPS);
    }

}
