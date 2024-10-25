Imports System.IO
Imports System.Net
Imports System.Runtime.ConstrainedExecution
Imports OpenTK.Mathematics

Public Class Mesh
	Implements IDisposable      '明示的にクラスを開放するために必要
	'public
	Public Sub New()
		mRadius = 0.0
		mSpecPower = 100.0
	End Sub
	Public Overloads Sub Dispose() Implements IDisposable.Dispose
		Dispose(True)
	End Sub
	Protected disposed = False     '開放処理が実施済みかのフラグ
	Protected Overridable Overloads Sub Dispose(ByVal disposing As Boolean)
		If Not Me.disposed Then
			If disposing Then
				'*** アンマネージリソースの開放
			End If
			'*** マネージドリソースの開放
		End If
		disposed = True
	End Sub
	Protected Overrides Sub Finalize()
		MyBase.Finalize()
		Dispose(False)
	End Sub
	Public Function Load(ByRef fileName As String, ByRef renderer As Renderer)
		If System.IO.File.Exists(fileName) Then
			'すべてのテキストを1つの文字列に読み込む
			Dim jsonText As String = File.ReadAllText(fileName)
			Dim root As Newtonsoft.Json.Linq.JObject = DirectCast(Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText), Newtonsoft.Json.Linq.JObject)
			Dim version As Integer = root("version")

			Return True
		Else
			Console.WriteLine("メッシュファイルが存在しません。")
			Return False
		End If

	End Function
    Public Sub Unload()
		mVertexInfo.Dispose()
		mVertexInfo = Nothing
	End Sub
	Public Function GetVertexInfo() As VertexInfo
		Return mVertexInfo
	End Function
	Public Function GetTexture(ByVal index As Integer) As Texture
		If (index < mTextures.Count()) Then
			Return mTextures(index)
		Else
			Return Nothing
		End If
	End Function

	Public Function GetShaderName() As String
        Return mShaderName
    End Function
    Public Function GetRadius() As Double
        Return mRadius
    End Function
    Public Function GetSpecPower() As Double
        Return mSpecPower
    End Function


    'private
    Private mTextures As List(Of Texture)
    Private mVertexInfo As VertexInfo
    Private mShaderName As String
    Private mRadius As Double
    Private mSpecPower As Double
End Class
