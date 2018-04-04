Imports System.IO
Imports System.IO.Ports
Imports System.Threading
Imports Microsoft.VisualBasic.FileIO

Public Class Main
    Dim Tension As Decimal
    Dim Courant As Decimal
    Dim Puissance As Decimal
    Dim Couple As Decimal
    Dim Vitesse As Decimal
    Shared _serialPort As SerialPort
    Private Shared WithEvents myTimer As New System.Windows.Forms.Timer()
    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        Me.Text = "EM Motor Test Bench"
        Me.BackColor = Color.Goldenrod
        Timer1.Enabled = True
        Label1.Text = "Battery Voltage"
        Label2.Text = "Motor Current"
        Label3.Text = "Speed"
        Label4.Text = "Torque"
        Label5.Text = "Power"
        Button1.Text = "Save to CSV"
        Button2.Text = "Quit"

        SerialPort1.DataBits = 8
        SerialPort1.Parity = Parity.None
        SerialPort1.StopBits = StopBits.One
        SerialPort1.Handshake = Handshake.None
        SerialPort1.Encoding = System.Text.Encoding.Default
    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        MsgBox("Thanks to use this application", 64, "BYE")
        SerialPort1.Close()
        End
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        'CreateCSVfile(Application.StartupPath & "\" & "CustomerRecords.csv", txtCustomerId.Text.ToString(), txtFirstName.Text.ToString(), txtLastName.Text.ToString(), txtPhoneNo.Text.ToString(), txtEmail.Text.ToString(), txtMessage.Text.ToString())
    End Sub

    Private Sub Timer1_Tick(sender As System.Object, e As System.EventArgs) Handles Timer1.Tick
        SerialPort1.Open()

        'edt_vitesse.Text = SerialPort1.ReadLine
        Dim testString1 As String = SerialPort1.ReadLine
        Dim CourantVal As String = String.Empty
        Dim TensionVal As String = String.Empty
        Dim VitesseVal As String = String.Empty
        Dim CoupleVal As String = String.Empty
        Dim liste() As Char = testString1.ToCharArray
        Dim CompteurChar As Integer = 0

        For Each ValeurChar In liste
            If (CompteurChar > 0 And CompteurChar <= 4) Then
                TensionVal += ValeurChar

            End If
            If (CompteurChar > 7 And CompteurChar <= 11) Then
                CourantVal += ValeurChar

            End If
            If (CompteurChar > 15 And CompteurChar <= 19) Then
                VitesseVal += ValeurChar

            End If
            If (CompteurChar > 22 And CompteurChar <= 26) Then
                CoupleVal += ValeurChar

            End If
            CompteurChar += 1
        Next

        Tension = Convert.ToDecimal(TensionVal)
        Courant = Convert.ToDecimal(CourantVal)
        Vitesse = Convert.ToDecimal(VitesseVal)
        Couple = Convert.ToDecimal(CoupleVal)
        Tension = ((55000 * (Tension)) / 1023) / 1000
        Tension = Decimal.Round(Tension, 3)
        Courant = ((((5000 * (Courant)) / 1023) - 2500) * (1000 / 66)) / 1000
        Courant = Decimal.Round(Courant, 3)
        Puissance = Tension * Courant
        TextBox1.Text = Tension
        TextBox2.Text = Courant
        TextBox3.Text = VitesseVal
        TextBox4.Text = CoupleVal
        TextBox5.Text = Puissance

        SerialPort1.Close()
    End Sub

    'Private Sub CreateCSVfile(ByVal _strCustomerCSVPath As String, ByVal _CustomerID As String, ByVal _FirstName As String, ByVal _LastName As String, ByVal _Phone As String, ByVal _Email As String, ByVal _Msg As String)
    '    Try
    '        Dim stLine As String = ""
    '        Dim objWriter As IO.StreamWriter = IO.File.AppendText(_strCustomerCSVPath)
    '        If IO.File.Exists(_strCustomerCSVPath) Then
    '            objWriter.Write(_CustomerID & ",")
    '            objWriter.Write(_FirstName & ",")
    '            objWriter.Write(_LastName & ",")
    '            objWriter.Write(_Email & ",")

    '            'If value contains comma in the value then you have to perform this opertions
    '            Dim append = If(_Msg.Contains(","), String.Format("""{0}""", _Msg), _Msg)
    '            stLine = String.Format("{0}{1},", stLine, append)
    '            objWriter.Write(stLine)

    '            objWriter.Write(_Phone)
    '            objWriter.Write(Environment.NewLine)
    '        End If
    '        objWriter.Close()
    '    Catch ex As Exception
    '    End Try
    'End Sub
End Class
