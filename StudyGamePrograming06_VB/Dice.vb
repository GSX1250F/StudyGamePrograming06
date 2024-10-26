Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework
Public Class Dice
    Inherits Actor
    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
        Dim v As Vector3 = New Vector3(200.0, -100.0, 0.0)
        SetPosition(v)
        SetScale(100.0)
        Dim mc As MeshComponent = New MeshComponent(Me)
        mc.SetMesh(game.GetRenderer().GetMesh("Assets/Dice.gpmesh"))
        mMoveComp = New MoveComponent(Me, 20)
    End Sub

    Public Overrides Sub UpdateActor(deltaTime As Double)
        MyBase.UpdateActor(deltaTime)
        Dim axis As Vector3 = New Vector3(1.0, -1.0, 1.0)
        axis.Normalize()
        Dim rotSpeedMax As Double = 30.0 * Math.PI
        Dim rotSpeed As Double = rotSpeedMax * deltaTime
        Dim v As Vector3 = rotSpeed * axis
        mMoveComp.SetRotSpeed(v)
    End Sub

    'private
    Dim mMoveComp As MoveComponent

End Class
