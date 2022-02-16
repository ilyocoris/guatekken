using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TSTKeyboardToState : MonoBehaviour
{
    TSTState state;
    void Start()
    {
        state = GetComponent<TSTState>();    
    }

    void Update()
    {
        state.move = new Vector2(Input.GetAxisRaw("Horizontal"),Input.GetAxisRaw("Vertical"));
        if (Input.GetKeyDown(KeyCode.Space))
        { 
            state.jump = true;
        }
    }
}
