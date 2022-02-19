using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class Animations {
    
    public string idle;
    public string run;
};

public class PlayerAnimator : MonoBehaviour
{
    Animator animator;
    Rigidbody2D rigid_body;
    PlayerState state;
    public Animations animations = new Animations();
    string currentState;

    void load_keyboard_character_animations(){
        // this will be done after detecting the character by bluetooth
        animations.idle = "keyboard_idle";
        animations.run = "keyboard_run";
    }

    void Start()
    {
        load_keyboard_character_animations();
        animator = GetComponent<Animator>();
        rigid_body = GetComponent<Rigidbody2D>();
        state = GetComponent<PlayerState>();
    }

    private void FixedUpdate() {
        // if(rigid_body.velocity == new Vector2(0,0)){
        //     ChangeAnimationState(animations.idle);
        // }
        //if(rigid_body.velocity.y == 0 & rigid_body.velocity.x != 0){
        if(Mathf.Abs(rigid_body.velocity.y) < 0.01f & rigid_body.velocity.x != 0){
            ChangeAnimationState(animations.run);
        }else{
            ChangeAnimationState(animations.idle);
        }
        
        
    }

    void ChangeAnimationState(string newState){
        // do not restart animations if already running
        if(currentState == newState) return;
        animator.Play(newState);
        currentState = newState;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
