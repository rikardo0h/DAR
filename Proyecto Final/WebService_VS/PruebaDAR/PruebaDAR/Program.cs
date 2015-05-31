using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;


namespace PruebaDAR
{
    class Program
    {
        static void Main(string[] args)
        {
            ATK atk = new ATK();
            atk.setType(1);
            atk.setCount(1);
            atk.setACK(1);
            atk.setMSG("Enviando");

            while (true)
            {
                Console.WriteLine("Enviando...");
                System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();

                clientSocket.Connect("74.208.234.113", 10000);

                NetworkStream serverStream = clientSocket.GetStream();
                serverStream.Write(atk.ObjetcToArray(), 0, atk.ObjetcToArray().Length);
                serverStream.Flush();
                clientSocket.Close();

                Console.ReadKey();
            }
            Console.ReadKey();
            
        }


        static void printATK(ATK a)
        {
            Console.WriteLine(a.getType());
            Console.WriteLine(a.getCount());
            Console.WriteLine(a.getACK());
            string msg = System.Text.Encoding.UTF8.GetString(a.getMSG());
            Console.WriteLine(msg);            
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
