Imports System.Drawing
Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework
Public Class Planes
    Inherits Actor
    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
		Dim start As Single = -1250.0
		Dim size As Single = 250.0
		'10個ずつ縦横に並べる
		For i As Integer = 0 To 9
			For j As Integer = 0 To 9
				Dim a As Plane = New Plane(game)
				a.SetPosition(New Vector3(start + i * size, start + j * size, -100.0))
				a.SetScale(10.0)
			Next
		Next

		'左右壁を作成
		Dim q = Quaternion.FromAxisAngle(Vector3.UnitX, -0.5 * Math.PI)
		For i As Integer = 0 To 9
			Dim a As Plane = New Plane(game)
			a.SetPosition(New Vector3(start + i * size, start - size, 0.0))
			a.SetScale(10.0)
			a.SetRotation(q)
		Next
		q = Quaternion.FromAxisAngle(Vector3.UnitX, 0.5 * Math.PI)
		For i As Integer = 0 To 9
			Dim a As Plane = New Plane(game)
			a.SetPosition(New Vector3(start + i * size, -start + size, 0.0))
			a.SetScale(10.0)
			a.SetRotation(q)
		Next

		'前後壁を作成
		q = Quaternion.Multiply(Quaternion.FromAxisAngle(Vector3.UnitZ, 0.5 * Math.PI), q)
		For i As Integer = 0 To 9
			Dim a As Plane = New Plane(game)
			a.SetPosition(New Vector3(start - size, start + i * size, 0.0))
			a.SetScale(10.0)
			a.SetRotation(q)
		Next
		q = Quaternion.Multiply(Quaternion.FromAxisAngle(Vector3.UnitZ, Math.PI), q)
		For i As Integer = 0 To 9
			Dim a As Plane = New Plane(game)
			a.SetPosition(New Vector3(-start + size, start + i * size, 0.0))
			a.SetScale(10.0)
			a.SetRotation(q)
		Next

	End Sub
End Class
