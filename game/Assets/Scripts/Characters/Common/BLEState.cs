using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/* 
    Common component for all Characters that will get called to update blutooth characteristics. 
*/
/*
    GYROSCOPE: 
        > Minimum speed for movement.
        > If no movement in X time, reset angle to 0.
        > compute custom deltatime since these are async calls

*/
public struct Gyroscope
{
    // angles of the controller
    public Vector3 angles;
    // last degrees per second reading from controller
    public Vector3 dps;
    // dps on last update
    public Vector3 lastDps;
    // timestamp of last update from controller
    public System.DateTime timeLastUpdate;
    // time the angle has not changed (dps too small)
    public Vector3 deltaTimeIdle;
    // minimum dps to compute a change in angle
    public float DPS_THRESHOLD;
    // minimum variation between dps updates to compute as change
    public float DPS_CHANGE_THRESHOLD;
    // idle time before  angle  reset
    public float DELTATIME_ANGLE_RESET;
};
public class BLEState : MonoBehaviour
{
    public bool DEBUG = false;
    public Gyroscope gyroscope;
    [Range(-20f, 20f)] public float testDPS;

    void Start()
    {
        // GYROSCOPE
        gyroscope.DPS_THRESHOLD = 8;
        gyroscope.DELTATIME_ANGLE_RESET = 600;
    }

    void Update()
    {
        if (DEBUG)
        {
            GyroscopeToState(new Vector3(testDPS, 0, 0));
            //Debug.Log(gyroscope.angles);
            Debug.Log(gyroscope.deltaTimeIdle[0]);
        }

        // Debug.Log(gyroscope.dps);
        Debug.Log(gyroscope.angles);

    }
    void OnGUI()
    {
        GUI.Label(new Rect(0, 0, 100, 100), gyroscope.angles[0].ToString());
    }
    public void GyroscopeToState(Vector3 gyroscopeDPS)
    {
        Debug.Log("BLEState.GyroscopeToState");
        // store DPS
        gyroscope.lastDps = gyroscope.dps;
        gyroscope.dps = gyroscopeDPS;
        // compute change for each angle
        float deltaTimeUpdate = (float)((System.DateTime.Now.Ticks - gyroscope.timeLastUpdate.Ticks) / 100000000000000000.0);
        for (int i = 0; i < 3; ++i)
        {
            float angular_speed = gyroscope.dps[i];
            if (Mathf.Abs(angular_speed) > gyroscope.DPS_THRESHOLD)
            {
                // reset time idle
                gyroscope.deltaTimeIdle[i] = 0;
                // update angle
                gyroscope.angles[i] += deltaTimeUpdate * angular_speed;
            }
            else
            {
                gyroscope.deltaTimeIdle[i] += deltaTimeUpdate;

                // reset angle if idle
                // if (gyroscope.deltaTimeIdle[i] > gyroscope.DELTATIME_ANGLE_RESET)
                // {
                //     Debug.Log(i);
                //     gyroscope.deltaTimeIdle[i] = 0;
                //     gyroscope.angles[i] = 0;
                // }
            }

        }
        return;
    }


}
