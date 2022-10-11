// <SNIPPET1>
using namespace System;
using namespace System::IO;
using namespace System::Security::Cryptography;
using namespace System::Text;

void EncryptTextToFile(String^ text, String^ path, array<Byte>^ key, array<Byte>^ iv);
String^ DecryptTextFromFile(String^ path, array<Byte>^ key, array<Byte>^ iv);

int main()
{
    try
    {
        array<Byte>^ key;
        array<Byte>^ iv;

        // Create a new DES object to generate a random key
        // and initialization vector (IV).
        {
            DES^ des;

            try
            {
                des = DES::Create();
                key = des->Key;
                iv = des->IV;
            }
            finally
            {
                delete des;
            }
        }

        // Create a string to encrypt.
        String^ original = "Here is some data to encrypt.";
        // The name/path of the file to write.
        String^ filename = "CText.enc";

        // Encrypt the string to a file.
        EncryptTextToFile(original, filename, key, iv);

        // Decrypt the file back to a string.
        String^ decrypted = DecryptTextFromFile(filename, key, iv);

        // Display the decrypted string to the console.
        Console::WriteLine(decrypted);
    }
    catch (Exception^ e)
    {
        Console::WriteLine(e->Message);
    }
}

void EncryptTextToFile(String^ text, String^ path, array<Byte>^ key, array<Byte>^ iv)
{
    FileStream^ fStream = nullptr;
    DES^ des = nullptr;
    ICryptoTransform^ encryptor = nullptr;
    CryptoStream^ cStream = nullptr;

    try
    {
        // Create or open the specified file.
        fStream = File::Open(path, FileMode::Create);
        // Create a new DES object.
        des = DES::Create();
        // Create a DES encryptor from the key and IV
        encryptor = des->CreateEncryptor(key, iv);
        // Create a CryptoStream using the FileStream and encryptor
        cStream = gcnew CryptoStream(fStream, encryptor, CryptoStreamMode::Write);
        
        // Convert the provided string to a byte array.
        array<Byte>^ toEncrypt = Encoding::UTF8->GetBytes(text);

        // Write the byte array to the crypto stream.
        cStream->Write(toEncrypt, 0, toEncrypt->Length);
    }
    catch (CryptographicException^ e)
    {
        Console::WriteLine("A Cryptographic error occurred: {0}", e->Message);
        throw;
    }
    finally
    {
        if (cStream != nullptr)
            delete cStream;

        if (encryptor != nullptr)
            delete encryptor;

        if (des != nullptr)
            delete des;

        if (fStream != nullptr)
            delete fStream;
    }
}

String^ DecryptTextFromFile(String^ path, array<Byte>^ key, array<Byte>^ iv)
{
    FileStream^ fStream = nullptr;
    DES^ des = nullptr;
    ICryptoTransform^ decryptor = nullptr;
    CryptoStream^ cStream = nullptr;
    StreamReader^ reader = nullptr;

    try
    {
        // Open the specified file
        fStream = File::OpenRead(path);
        // Create a new DES object.
        des = DES::Create();
        // Create a DES decryptor from the key and IV
        decryptor = des->CreateDecryptor(key, iv);
        // Create a CryptoStream using the FileStream and decryptor
        cStream = gcnew CryptoStream(fStream, decryptor, CryptoStreamMode::Read);
        // Create a StreamReader to turn the bytes back into text
        reader = gcnew StreamReader(cStream, Encoding::UTF8);

        // Read back all of the text from the StreamReader, which receives
        // the decrypted bytes from the CryptoStream, which receives the
        // encrypted bytes from the FileStream.
        return reader->ReadToEnd();
    }
    catch (CryptographicException^ e)
    {
        Console::WriteLine("A Cryptographic error occurred: {0}", e->Message);
        throw;
    }
    finally
    {
        if (cStream != nullptr)
            delete cStream;

        if (decryptor != nullptr)
            delete decryptor;

        if (des != nullptr)
            delete des;

        if (fStream != nullptr)
            delete fStream;
    }
}

// </SNIPPET1>
