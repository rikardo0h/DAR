using System;
using System.Collections;
using System.Net.Sockets;
using System.Text;


namespace PruebaDAR
{
    class Program
    {
        static void Main(string[] args)
        {
            ATK atk = new ATK();
            atk.setType(2);
            atk.setCount(1);
            atk.setACK(1);
            atk.setMSG("Solicitando SCANIP's");

            
            byte[] buffer = new byte[103];
            

            while (true)
            {
                Console.WriteLine("Conectando...");
                
                try
                {
                    System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();
                    //clientSocket.Connect("74.208.234.113", 10000);
                    clientSocket.Connect("192.168.1.82", 10000);
                    NetworkStream serverStream = clientSocket.GetStream();

                    Console.Out.WriteLine("Enviando");
                    Console.Out.WriteLine("Teclee 1 ó 2: ");
                    String a = Console.In.ReadLine();
                    atk.setType(Convert.ToByte(a));
                    Console.Out.WriteLine("Opcion: " + atk.getType());
                    serverStream.Write(atk.ObjetcToArray(), 0, atk.ObjetcToArray().Length);

                    serverStream.Flush();

                    Console.Out.WriteLine("Recibiendo");
                    serverStream.Read(buffer, 0, atk.ObjetcToArray().Length);
                    atk.ArrayToObjetc(buffer);
                    printATK(atk);
                    serverStream.Flush();
                    //Console.Out.WriteLine("Recibido: " + Encoding.ASCII.GetString(atk.getMSG()));
                    int count = atk.getCount();
                    Console.Out.WriteLine("Count: " + count);
                    String msjFull = "";
                    ArrayList lByte = new ArrayList();
                    for (int i = 0; i < count; i++)
                    {
                        ATK aTemp = new ATK();
                        serverStream.Read(buffer, 0, 103);
                        aTemp.ArrayToObjetc(buffer);
                        lByte.Add(aTemp.getMSG());
                        Console.Out.WriteLine("Recibiendo: " + i + " de " + count);
                        Console.Out.WriteLine("Recibido: " + Encoding.ASCII.GetString(buffer));
                        serverStream.Write(aTemp.ObjetcToArray(), 0, 103);
                        serverStream.Flush();
                    }

                    Console.Out.WriteLine(lByte.Count);
                    foreach(byte[] it in lByte)
                    {
                        Console.Out.WriteLine("Mensajes: " + Encoding.ASCII.GetString(it));
                    }
                    //Console.Out.WriteLine(Encoding.ASCII.GetString(lATK[4].getMSG()));
                    

                    Console.Out.WriteLine("El MSJ COMPLETO ES: \n" + msjFull);

                    clientSocket.Close();
                }catch(Exception e)
                {
                    Console.Out.WriteLine(e.Message);
                }

                //serverStream.Flush();                
                Console.ReadKey();
            }
        }


        static void printATK(ATK a)
        {
            Console.WriteLine("Type: " + a.getType());
            Console.WriteLine("Count: " + a.getCount());
            Console.WriteLine("ACK: " + a.getACK());
            string msg = System.Text.Encoding.UTF8.GetString(a.getMSG());
            Console.WriteLine("Mensaje: " + msg);            
        }

        static void printATKFullObject(ATK a)
        {
            foreach (byte element in a.ObjetcToArray())
            {
                Console.WriteLine("{0} = {1}", element, (char)element);
            }
        }
    }
}
