Imports System.Drawing
Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework
Public Class MeshActors
    Inherits Actor
    Sub New(ByRef game As Game)
        MyBase.New(game)
        Dim a As Actor
        Dim meshfile As String
		' サイコロ
		meshfile = "Assets/Dice.gpmesh"     ' BasicMesh	
		a = New Dice(game, meshfile)
		a.SetPosition(New Vector3(700.0, 500.0, 0.0))

		meshfile = "Assets/Dice2.gpmesh"        ' LambertMesh
		a = New Dice(game, meshfile)
		a.SetPosition(New Vector3(700.0, 0.0F, 0.0))

		meshfile = "Assets/Dice3.gpmesh"        ' PhongMesh
		a = New Dice(game, meshfile)
		a.SetPosition(New Vector3(700.0, -500.0F, 0.0))

		' 球
		meshfile = "Assets/Sphere.gpmesh"       ' BasicMesh	
		a = New Sphere(game, meshfile)
		a.SetPosition(New Vector3(-500.0F, 700.0F, 0.0))

		meshfile = "Assets/Sphere2.gpmesh"      ' LambertMesh
		a = New Sphere(game, meshfile)
		a.SetPosition(New Vector3(0.0, 700.0, 0.0))

		meshfile = "Assets/Sphere3.gpmesh"      ' PhongMesh
		a = New Sphere(game, meshfile)
		a.SetPosition(New Vector3(500.0, 700.0, 0.0))

		' レーシングカー
		meshfile = "Assets/RacingCar.gpmesh"        ' BasicMesh	
		a = New RacingCar(game, meshfile)
		a.SetPosition(New Vector3(500.0, -700.0, -100.0))

		meshfile = "Assets/RacingCar2.gpmesh"       ' LambertMesh
		a = New RacingCar(game, meshfile)
		a.SetPosition(New Vector3(0.0, -700.0, -100.0))

		meshfile = "Assets/RacingCar3.gpmesh"       ' PhongMesh
		a = New RacingCar(game, meshfile)
		a.SetPosition(New Vector3(-500.0, -700.0, -100.0))

		' 壁と床
		meshfile = "Assets/Plane3.gpmesh"       ' PhongMesh
		Dim start As Single = -1250.0
		Dim size As Single = 250.0
		' 10個ずつ縦横に並べる
		For i As Integer = 0 To 9
			For j As Integer = 0 To 9
				a = New Plane(game, meshfile)
				a.SetPosition(New Vector3(start + i * size, start + j * size, -100.0))
			Next
		Next
		' 左右壁を作成
		Dim q = Quaternion.FromAxisAngle(Vector3.UnitX, -0.5 * Math.PI)
		For i As Integer = 0 To 9
			a = New Plane(game, meshfile)
			a.SetPosition(New Vector3(start + i * size, start - size, 0.0))
			a.SetRotation(q)
		Next
		q = Quaternion.FromAxisAngle(Vector3.UnitX, 0.5 * Math.PI)
		For i As Integer = 0 To 9
			a = New Plane(game, meshfile)
			a.SetPosition(New Vector3(start + i * size, -start + size, 0.0))
			a.SetRotation(q)
		Next

		' 前後壁を作成
		q = Quaternion.Multiply(Quaternion.FromAxisAngle(Vector3.UnitZ, 0.5 * Math.PI), q)
		For i As Integer = 0 To 9
			a = New Plane(game, meshfile)
			a.SetPosition(New Vector3(start - size, start + i * size, 0.0))
			a.SetRotation(q)
		Next
		q = Quaternion.Multiply(Quaternion.FromAxisAngle(Vector3.UnitZ, Math.PI), q)
		For i As Integer = 0 To 9
			a = New Plane(game, meshfile)
			a.SetPosition(New Vector3(-start + size, start + i * size, 0.0))
			a.SetRotation(q)
		Next

	End Sub
End Class

Public Class Dice
	Inherits Actor
	'public
	Sub New(ByRef game As Game, ByRef meshfile As String)
		MyBase.New(game)
		SetScale(100.0)
		Dim mc As MeshComponent = New MeshComponent(Me)
		mc.SetMesh(game.GetRenderer().GetMesh(meshfile))
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

Public Class Plane
	Inherits Actor
	'public
	Sub New(ByRef game As Game, ByRef meshfile As String)
		MyBase.New(game)
		SetScale(10.0)
		Dim mc As MeshComponent = New MeshComponent(Me)
		mc.SetMesh(game.GetRenderer.GetMesh(meshfile))
	End Sub
End Class

Public Class RacingCar
	Inherits Actor
	'public
	Sub New(ByRef game As Game, ByRef meshfile As String)
		MyBase.New(game)
		SetScale(1.0)
		Dim mc = New MeshComponent(Me)
		mc.SetMesh(game.GetRenderer.GetMesh(meshfile))
		mMoveComp = New MoveComponent(Me, 20)
	End Sub
	Public Overrides Sub UpdateActor(deltaTime As Single)
		MyBase.UpdateActor(deltaTime)
		Dim w As Single = Math.PI / 4
		'Dim r As Single = Math.Sqrt(GetPosition.X * GetPosition.X + GetPosition.Y * GetPosition.Y)
		'Dim x As Single = GetPosition.X * Math.Cos(w * deltaTime) + GetPosition.Y * Math.Sin(w * deltaTime)
		'Dim y As Single = GetPosition.Y * Math.Cos(w * deltaTime) - GetPosition.X * Math.Sin(w * deltaTime)
		'SetPosition(New Vector3(x, y, -100.0))
		Dim q As Quaternion = GetRotation()
		Dim inc As Quaternion = Quaternion.FromAxisAngle(Vector3.UnitZ, -w * deltaTime)
		q = Quaternion.Multiply(inc, q)
		SetRotation(q)
	End Sub
	'private
	Dim mMoveComp As MoveComponent
End Class

Public Class Sphere
	Inherits Actor
	'public
	Sub New(ByRef game As Game, ByRef meshfile As String)
		MyBase.New(game)
		Dim q As Quaternion = New Quaternion(Vector3.UnitX, -23.5 / 180.0 * Math.PI)
		SetRotation(q)
		SetScale(5.0)
		Dim mc As MeshComponent = New MeshComponent(Me)
		mc.SetMesh(game.GetRenderer().GetMesh(meshfile))
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