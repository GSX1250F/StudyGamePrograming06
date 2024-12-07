Imports System.Drawing
Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework

Public Class CameraActor
    Inherits Actor

    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
        SetPosition(New Vector3(0.0, 0.0, 100.0))
        mMoveComp = New MoveComponent(Me, 30)

        'スポットライト
        Dim sl As SpotLight
        sl.mPosition = GetPosition()
        sl.mDirection = GetForward()
        Dim color = New Vector3(1.0, 1.0, 1.0)
        sl.mDiffuseColor = color
        sl.mSpecColor = color
        sl.mAttenuation = 0.9
        sl.mCornAngle = Math.PI / 8.0
        sl.mFalloff = 200.0
        game.GetRenderer().AddSpotLight(sl)
    End Sub

    Public Overrides Sub UpdateActor(ByVal deltaTime As Single)
        MyBase.UpdateActor(deltaTime)

        ' カメラの位置と方向を更新
        Dim cameraPos As Vector3 = GetPosition()
        Dim cameraTarget As Vector3 = GetPosition() + GetForward() * 100.0F
        Dim cameraUp As Vector3 = Vector3.UnitZ

        Dim view As Matrix4 = Matrix4.LookAt(cameraPos, cameraTarget, cameraUp)
        GetGame().GetRenderer().SetViewMatrix(view)

        'スポットライトの位置と方向を更新
        Dim sl As SpotLight
        Dim sls As List(Of SpotLight) = GetGame().GetRenderer().GetSpotLights()
        sl = sls(0)
        sl.mPosition = GetPosition()
        sl.mDirection = GetForward()
        sls(0) = sl
        GetGame().GetRenderer().SetSpotLights(sls)
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
