// Order of execution for event functions:
// https://docs.unity3d.com/Manual/ExecutionOrder.html


using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyboardCharacter : MonoBehaviour
{
    PlayerState state;
    // public float speed = 200;
    // Vector2 move;
    // Rigidbody2D rigid_body;
    // Start is called before the first frame update
    void Start()
    {
        // rigid_body = GetComponent<Rigidbody2D>();
        state = GetComponent<PlayerState>();
        
    }

    void FixedUpdate(){
        // for inertia-like movement, maybe for a tank//heavy character?
        // rigid_body.AddForce(move*speed*Time.deltaTime);
        // rigid_body.velocity = new Vector2(move.x*speed*Time.deltaTime,rigid_body.velocity.y);

    }

    // Update is called once per frame
    void Update()
    {
        state.move = new Vector2(Input.GetAxisRaw("Horizontal"),Input.GetAxisRaw("Vertical"));
    }
}
