Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework

Public Class CameraActor
    Inherits Actor

    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
        Dim v As Vector3 = New Vector3(-200.0, 0.0, 150.0)
        SetPosition(v)
        mMoveComp = New MoveComponent(Me, 30)
    End Sub

    Public Overrides Sub UpdateActor(deltaTime As Single)
        MyBase.UpdateActor(deltaTime)

        ' カメラの位置と方向を更新
        Dim cameraPos As Vector3 = GetPosition()
        Dim cameraTarget As Vector3 = GetPosition() + GetForward() * 100.0F
        Dim cameraUp As Vector3 = Vector3.UnitZ

        Dim view As Matrix4 = Matrix4.LookAt(cameraPos, cameraTarget, cameraUp)
        GetGame().GetRenderer().SetViewMatrix(view)
    End Sub

    Public Overrides Sub ActorInput(keyState As KeyboardState)
        MyBase.ActorInput(keyState)
        Dim forwardSpeed As Single = 0.0
        Dim rotSpeed As Single = 0.0
        If (keyState.IsKeyDown(Keys.Up)) Then
			forwardSpeed += 500
		ElseIf (keyState.IsKeyDown(Keys.Down)) Then
			forwardSpeed += -500
		ElseIf (keyState.IsKeyDown(Keys.Left)) Then
            rotSpeed += Math.PI
        ElseIf (keyState.IsKeyDown(Keys.Right)) Then
            rotSpeed -= Math.PI
        End If
		mMoveComp.SetVelocity(forwardSpeed * GetForward())
        mMoveComp.SetRotSpeed(rotSpeed * GetUpward())
    End Sub

    'private
    Private mMoveComp As MoveComponent

End Class
