Imports System.IO.Ports

Public Class Settings
    Shared _serialPort As SerialPort
    Dim change1 As Boolean
    Dim change2 As Boolean
    Private Sub Settings_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        Me.Text = "Serial Port Settings"
        Label1.Text = "Select Serial Port"
        Label2.Text = "Select Baudrate"
        Button1.Text = "Start Application"
        Button1.Enabled = False
        Button2.Text = "Help"
        Button2.Focus()

        Dim AvailablePorts() As String = SerialPort.GetPortNames()
        Dim Port As String

        For Each Port In AvailablePorts
            ComboBox1.Items.Add(Port)
        Next Port

        ComboBox2.Items.Add("9600")
        ComboBox2.Items.Add("19200")

        MsgBox("Welcome to the Eco-Marathon 2018 test bench application.", 64, "WELCOME")
        Me.Show()
        


    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(sender As System.Object, e As System.EventArgs) Handles ComboBox1.SelectedIndexChanged
        Main.SerialPort1.PortName = ComboBox1.Text
        If ComboBox1.Text <> " " Then
            change1 = True
        Else
            change1 = False
        End If
        'Main.TextBox1.Text = ComboBox1.Text

        If change1 And change2 Then
            Button1.Enabled = True
        End If
    End Sub

    Private Sub ComboBox2_SelectedIndexChanged(sender As System.Object, e As System.EventArgs) Handles ComboBox2.SelectedIndexChanged
        Main.SerialPort1.BaudRate = ComboBox2.Text
        If ComboBox2.Text <> " " Then
            change2 = True
        Else
            change2 = False
        End If
        If change1 And change2 Then
            Button1.Enabled = True
        End If
    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        MsgBox("To operate this software you need first to select the serial port and the baudrate.", 64, "Help?")
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Main.Show()
        Me.Hide()
    End Sub
End Class