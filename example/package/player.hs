Horizon @Register class Player : HorizonActor {
  Components
  {
    CapsuleComponent Capsule
    {
      height=32 size=12

      CameraComponent Camera;
    }
  }

  override OnBeginPlay()
  {
    log("Hello from Player class");
    Super();  //Calls the nearest parent super function
  }

  override Tick(float deltaTime)
  {
    float dt = deltaTime;
    log("FPS is {1/dt}!");
  }

  override OnEndPlay()
  {
    Camera.SetFieldOfView(30.0);
  }
  
  @Input(Jump, Pressed | Released)
  HandleJump()  //Execute when jump is pressed and when its released
  {
    SetZVelocity(100.0);
  }
  
  @Input(MoveForward)
  HandleMoveForward(float scale)
  {
    Vector3 vec = GetForwardVector(Camera.GetRotation());
    AddLocationOffset(vec * scale);
  }
}

