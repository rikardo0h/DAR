using PruebaDAR;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Web;
using System.Web.Services;

namespace PruebaWebDAR
{
    /// <summary>
    /// Summary description for Receptor
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
            
    public class Receptor : System.Web.Services.WebService
    {

        [WebMethod]
        public string HelloWorld()
        {
            return "Hello World";
        }

        [WebMethod]
        public void solicitar()
        {
            ATK atk = new ATK();
            atk.setType(1);
            atk.setCount(1);
            atk.setACK(1);
            atk.setMSG("Enviando");
                
            System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();

            clientSocket.Connect("74.208.234.113", 10000);

            NetworkStream serverStream = clientSocket.GetStream();
            serverStream.Write(atk.ObjetcToArray(), 0, atk.ObjetcToArray().Length);
            serverStream.Flush();
            clientSocket.Close();
        }
    }
}
