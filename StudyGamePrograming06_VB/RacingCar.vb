Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework
Public Class RacingCar
    Inherits Actor
    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
        SetPosition(New Vector3(0.0, 500.0, -100.0))
        'Dim q = Quaternion.FromAxisAngle(Vector3.UnitZ, Math.PI)
        'SetRotation(q)
        SetScale(1.0)
        Dim mc = New MeshComponent(Me)
        mc.SetMesh(game.GetRenderer.GetMesh("Assets/RacingCar.gpmesh"))
        mMoveComp = New MoveComponent(Me, 20)
    End Sub
    Public Overrides Sub UpdateActor(deltaTime As Single)
        MyBase.UpdateActor(deltaTime)
        Dim w As Single = Math.PI / 2
        Dim r As Single = Math.Sqrt(GetPosition.X * GetPosition.X + GetPosition.Y * GetPosition.Y)
        Dim x As Single = GetPosition.X * Math.Cos(w * deltaTime) + GetPosition.Y * Math.Sin(w * deltaTime)
        Dim y As Single = GetPosition.Y * Math.Cos(w * deltaTime) - GetPosition.X * Math.Sin(w * deltaTime)
        SetPosition(New Vector3(x, y, -100.0))
        Dim q As Quaternion = GetRotation()
        Dim inc As Quaternion = Quaternion.FromAxisAngle(Vector3.UnitZ, -w * deltaTime)
        q = Quaternion.Multiply(inc, q)
        SetRotation(q)
    End Sub
    'private
    Dim mMoveComp As MoveComponent
End Class
