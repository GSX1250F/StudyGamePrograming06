Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework
Public Class Sphere
    Inherits Actor
    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
        SetPosition(New Vector3(200.0, 100.0, 0.0))
        Dim q As Quaternion = New Quaternion(Vector3.UnitX, -23.5 / 180.0 * Math.PI)
        SetRotation(q)
        SetScale(5.0)
        Dim mc As MeshComponent = New MeshComponent(Me)
        mc.SetMesh(game.GetRenderer().GetMesh("Assets/Sphere.gpmesh"))
        mMoveComp = New MoveComponent(Me, 20)
    End Sub

    Public Overrides Sub UpdateActor(deltaTime As Single)
        MyBase.UpdateActor(deltaTime)
        Dim mAxis As Vector3 = New Vector3(0.0, Math.Cos(66.5 / 180.0 * Math.PI), Math.Sin(66.5 / 180.0 * Math.PI))
        Dim rotSpeedMax As Single = 5.0 * Math.PI
        Dim rotSpeed As Single = rotSpeedMax * deltaTime
        mMoveComp.SetRotSpeed(rotSpeed * mAxis)
    End Sub

    'private
    Dim mMoveComp As MoveComponent
End Class
