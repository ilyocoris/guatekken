using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct Controller
{
    public bool KEYBOARD;
    public Vector2 move;
    public bool jump;
};

public class TSTMovement : MonoBehaviour
{
    Rigidbody2D rigidBody;
    BLEState state;
    // movement parameters
    public int speed;
    public float jumpForce;
    public bool isGrounded;
    public float detectGroundRay;
    public LayerMask groundMask;
    public Controller controller;



    void Start()
    {
        state = GetComponent<BLEState>();
        rigidBody = GetComponent<Rigidbody2D>();
        controller.move = new Vector2(0, 0);
        controller.jump = false;
        controller.KEYBOARD = false;
        //
        speed = 50;
        jumpForce = 300;
        detectGroundRay = 0.55f;

        groundMask = 1 << LayerMask.NameToLayer("groundLayer");
    }

    void Update()
    {
        if (Input.GetKeyDown("k"))
        {
            controller.KEYBOARD = !controller.KEYBOARD;
        }
        if (controller.KEYBOARD)
        {
            KeyboardToController();
        }
        else
        {
            BLEStateToController();
        }
    }

    void BLEStateToController()
    {
        /* 
            Logic for transforming BLE state to controller actions for character 
        */

        if (state.gyroscope.angles.x > 30)
        {
            controller.move.x = 1;
        }
        else if (state.gyroscope.angles.x < -30)
        {
            controller.move.x = -1;
        }
        else
        {
            controller.move.x = 0;
        }
    }

    void KeyboardToController()
    {
        controller.move = new Vector2(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"));
        if (Input.GetKeyDown(KeyCode.Space))
        {
            controller.jump = true;
        }
    }



    void FixedUpdate()
    {
        // for inertia-like movement, maybe for a tank//heavy character?
        // rigidBody.AddForce(move*speed*Time.deltaTime);
        // Grounded Check
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, detectGroundRay, groundMask);
        if (hit.collider != null)
        {
            isGrounded = true;
        }
        else
        {
            isGrounded = false;
        }
        // xy Movement
        rigidBody.velocity = new Vector2(controller.move.x * speed * Time.deltaTime, rigidBody.velocity.y);
        // Jump
        if (controller.jump & isGrounded)
        {
            controller.jump = false;
            rigidBody.AddForce(new Vector2(0, jumpForce * Time.deltaTime), ForceMode2D.Impulse);
        }
    }
}
