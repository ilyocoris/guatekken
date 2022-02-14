using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public int speed;

    PlayerState state;
    Rigidbody2D rigid_body;
    public bool is_grounded;
    public float jump_force;
    public LayerMask groundMask;
    public float ground_ray = 1;
    // Start is called before the first frame update
    void Start()
    {
        speed = 100;
        jump_force = 300;
        state = GetComponent<PlayerState>();
        rigid_body = GetComponent<Rigidbody2D>();
        groundMask = 1 << LayerMask.NameToLayer("groundLayer");   

    }

    void FixedUpdate(){
        // for inertia-like movement, maybe for a tank//heavy character?
        // rigid_body.AddForce(move*speed*Time.deltaTime);
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, ground_ray,groundMask);
        if(hit.collider != null){
            is_grounded = true;
        }else{
            is_grounded = false;
        }
        rigid_body.velocity = new Vector2(state.move.x*speed*Time.deltaTime,rigid_body.velocity.y); 
        if(state.jump & is_grounded){
            state.jump = false;
            rigid_body.AddForce(new Vector2(0,jump_force*Time.deltaTime),ForceMode2D.Impulse);
        }

        



    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
