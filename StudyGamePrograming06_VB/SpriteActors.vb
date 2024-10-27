Imports OpenTK.Mathematics
Imports OpenTK.Windowing.GraphicsLibraryFramework
Public Class SpriteActors
    Inherits Actor
    'public
    Sub New(ByRef game As Game)
        MyBase.New(game)
		Dim a As Actor = New Actor(game)
		a.SetPosition(New Vector3(-350.0, -350.0, 0.0))
		Dim sc As SpriteComponent = New SpriteComponent(a, 5)
		sc.SetTexture(game.GetRenderer.GetTexture("Assets/HealthBar.png"))

		a = New Actor(game)
		a.SetPosition(New Vector3(375.0, -275.0, 0.0))
		a.SetScale(0.75)
		sc = New SpriteComponent(a, 10)
		sc.SetTexture(game.GetRenderer.GetTexture("Assets/Radar.png"))
	End Sub

End Class
