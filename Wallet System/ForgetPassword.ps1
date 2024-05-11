$smtpServer = "smtp.gmail.com"
$smtpPort = 587
$emailFrom = "kingmomen510@gmail.com"
$emailTo = "
$subject = "New Account Password"
$body = "your random genrated code is 
$password = ConvertTo-SecureString "ipwr tkmy xdbs jgbk " -AsPlainText -Force
$credential = New-Object System.Management.Automation.PSCredential ($emailFrom, $password)
$mailMessage = New-Object System.Net.Mail.MailMessage
$mailMessage.Subject = $subject
$mailMessage.Body = $body
$mailMessage.From = $emailFrom
$mailMessage.To.Add($emailTo)
$smtpClient = New-Object System.Net.Mail.SmtpClient($smtpServer, $smtpPort)
$smtpClient.EnableSsl = $true
$smtpClient.Credentials = $credential
$smtpClient.Send($mailMessage)
