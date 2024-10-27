Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework
Public Class Dice
    Inherits Actor
    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
        SetPosition(New Vector3(200.0, -100.0, 0.0))
        SetScale(100.0)
        Dim mc As MeshComponent = New MeshComponent(Me)
        mc.SetMesh(game.GetRenderer().GetMesh("Assets/Dice.gpmesh"))
        mMoveComp = New MoveComponent(Me, 20)
    End Sub

    Public Overrides Sub UpdateActor(deltaTime As Single)
        MyBase.UpdateActor(deltaTime)
        Dim axis As Vector3 = New Vector3(1.0, 1.0, 1.0)
        axis.Normalize()
        Dim rotSpeedMax As Single = -30.0 * Math.PI
        Dim rotSpeed As Single = rotSpeedMax * deltaTime
        mMoveComp.SetRotSpeed(rotSpeed * axis)
    End Sub

    'private
    Dim mMoveComp As MoveComponent

End Class
