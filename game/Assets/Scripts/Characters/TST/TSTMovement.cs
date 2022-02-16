using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TSTMovement : MonoBehaviour
{
    Rigidbody2D rigidBody;
    TSTState state;
    // movement parameters
    public int speed;
    public float jumpForce;
    public bool isGrounded;
    public float detectGroundRay;
    public LayerMask groundMask;
    
    void Start()
    {
        state = GetComponent<TSTState>();
        rigidBody = GetComponent<Rigidbody2D>();
        //
        speed = 100;
        jumpForce = 300;
        detectGroundRay = 0.55f;

        groundMask = 1 << LayerMask.NameToLayer("groundLayer");          
    }

    void FixedUpdate(){
        // for inertia-like movement, maybe for a tank//heavy character?
        // rigidBody.AddForce(move*speed*Time.deltaTime);
        // Grounded Check
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, detectGroundRay,groundMask);
        if(hit.collider != null){
            isGrounded = true;
        }else{
            isGrounded = false;
        }
        // xy Movement
        rigidBody.velocity = new Vector2(state.move.x*speed*Time.deltaTime,rigidBody.velocity.y); 
        // Jump
        if(state.jump & isGrounded){
            state.jump = false;
            rigidBody.AddForce(new Vector2(0,jumpForce*Time.deltaTime),ForceMode2D.Impulse);
        }
    }
}
