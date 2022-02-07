using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

struct Characteristic{
    int[] value;
};

// struct Controller{
//     Dictionary <string,Characteristic> characteristics;
// };

public class DataLake : MonoBehaviour
{
    private 

    // Start is called before the first frame update
    void Start()
    {
        // ConnectToBLE();
        // this.controllers = new Dictionary<string, Controller>();
        // Controller controller = new Controller();
        // this.controllers.Add("controller_id",controller);
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void UpdateCharacteristicData(){
        Debug.Log("hello");
    }

    void InitializePlayerDataStructure(string controllerId){
        if(controllerId=="TestController"){

        }

    }
}
