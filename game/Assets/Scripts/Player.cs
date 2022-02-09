using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public int speed;

    PlayerState state;
    Rigidbody2D rigid_body;

    // Start is called before the first frame update
    void Start()
    {
        speed = 10;
        state = GetComponent<PlayerState>();
        rigid_body = GetComponent<Rigidbody2D>();
    }

    void FixedUpdate(){
        // for inertia-like movement, maybe for a tank//heavy character?
        // rigid_body.AddForce(move*speed*Time.deltaTime);
        rigid_body.velocity = new Vector2(state.move.x*speed*Time.deltaTime,rigid_body.velocity.y);

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
