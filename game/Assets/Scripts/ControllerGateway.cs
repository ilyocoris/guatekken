using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct Player{
    public Object Character;
    public Vector2 startingPosition; 
    public string controllerId; 
    public string playerId;
};

public struct ControllerConnectionInfo{
    public string controllerId;
    public string playerId;
};

public struct SensorXYZInfo{
    float x;
    float y;
    float z;
    public string playerId;
};

public class ControllerGateway : MonoBehaviour
{
    //Could be a List instead of a dictionary? List<Player> Players = new List<Player>();
    public Dictionary<string, Player> Players = new Dictionary<string, Player>();
    // Start is called before the first frame update

    void Start(){
        // ControllerConnection("{\"playerId\":\"Player1\",\"controllerId\":\"TestController\"}");
    }

    void ControllerConnection(string jsConnectionInfo){
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
        switch(connectionInfo.controllerId){
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
        newPlayer.Character = Resources.Load(CharacterPrefabPath); 
        newPlayer.controllerId = connectionInfo.controllerId;
        newPlayer.playerId = connectionInfo.playerId;
        newPlayer.startingPosition = getPlayerStartingPosition(connectionInfo.playerId);
        Players[connectionInfo.playerId] = newPlayer;
        Instantiate(Players[connectionInfo.playerId].Character, Players[connectionInfo.playerId].startingPosition,Quaternion.identity);  
        Debug.Log("Hello");   
    }

    Vector2 getPlayerStartingPosition(string playerId){
        /*
            Returns a default starting position for each player.
        */
        Vector2 startingPosition;
        switch(playerId){
            case "Player1":
                startingPosition = new Vector2(-3,0);
                break;
            case "Player2":
                startingPosition = new Vector2(3,0);
                break;
            default:
                startingPosition = new Vector2(0,0);
                break;
        }
        return startingPosition;
    }

    void UpdateGyroscope(string GyroscopeInfo){
        SensorXYZInfo gyroscopeUpdateInfo = JsonUtility.FromJson<SensorXYZInfo>(GyroscopeInfo);

    }
    

    // Update is called once per frame
    void Update()
    {
        
    }
}
