Imports System.IO
Imports System.IO.Ports
Imports System.Threading
Imports Microsoft.VisualBasic.FileIO
'Laurent Chevalier 2018
Public Class Main
    Dim Tension As Decimal
    Dim Courant As Decimal
    Dim Puissance As Decimal
    Dim Couple As Decimal
    Dim Vitesse As Decimal
    Dim boutonclick_save As Boolean = False
    Dim bouton_Quit As Boolean = False
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
        bouton_Quit = True
        MsgBox("Thanks to use this application", 64, "BYE")
        SerialPort1.Close()
        End
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        boutonclick_save = True
        'CreateCSVfile(Application.StartupPath & "\" & "CustomerRecords.csv", txtCustomerId.Text.ToString(), txtFirstName.Text.ToString(), txtLastName.Text.ToString(), txtPhoneNo.Text.ToString(), txtEmail.Text.ToString(), txtMessage.Text.ToString())
    End Sub

    Private Sub Timer1_Tick(sender As System.Object, e As System.EventArgs) Handles Timer1.Tick
        SerialPort1.Open()

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

        If boutonclick_save Then
            CreateCSVfile(Application.StartupPath & "\" & "Test_Bench_Measures.csv", "U" & TensionVal, "IM" & CourantVal, "RPM" & VitesseVal, "Nm" & CoupleVal)
        End If
    End Sub

    Private Sub CreateCSVfile(ByVal _strCustomerCSVPath As String, ByVal _Tension As String, ByVal _Courant As String, ByVal _Vitesse As String, ByVal _Couple As String)
        Try
            Dim stLine As String = ""
            Dim objWriter As IO.StreamWriter = IO.File.AppendText(_strCustomerCSVPath)
            If IO.File.Exists(_strCustomerCSVPath) Then
                objWriter.Write(_Tension & ";")
                objWriter.Write(_Courant & ";")
                objWriter.Write(_Vitesse & ";")
                objWriter.Write(_Couple)

                ''If value contains comma in the value then you have to perform this opertions
                'Dim append = If(_Msg.Contains(","), String.Format("""{0}""", _Msg), _Msg)
                'stLine = String.Format("{0}{1},", stLine, append)
                
                objWriter.Write(Environment.NewLine)
            End If
            If bouton_Quit Then
                objWriter.Close()
            End If
            objWriter.Close()
        Catch ex As Exception
        End Try
    End Sub
End Class
