using PruebaDAR;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
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
    //[System.Web.Script.Services.ScriptService]
            
    public class Receptor : System.Web.Services.WebService
    {

        [WebMethod]
        public string HelloWorld()
        {
            return "Hello World";
        }

        [WebMethod]
        public String scanIPS()
        {
            ATK atk = new ATK();
            atk.setType(2);
            atk.setCount(1);
            atk.setACK(1);
            atk.setMSG("Solicitando SCANIP's");
            var jsonSerializer = new System.Web.Script.Serialization.JavaScriptSerializer();
            String json = "";
            String msj = "";
            String [] m = null;
            byte[] buffer = new byte[103];
            ArrayList lByte = new ArrayList();
            List<String> lPaquetes = new List<String>();
          
            try 
            {
                System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();
                //clientSocket.Connect("74.208.234.113", 10000);
                clientSocket.Connect("192.168.1.82", 10000);
                NetworkStream serverStream = clientSocket.GetStream();

                serverStream.Write(atk.ObjetcToArray(), 0, atk.ObjetcToArray().Length);
                serverStream.Flush();

                serverStream.Read(buffer, 0, atk.ObjetcToArray().Length);
                atk.ArrayToObjetc(buffer);
                serverStream.Flush();
                
                
                int count = atk.getCount();
                for (int i = 0; i < count; i++)
                {
                    ATK aTemp = new ATK();
                    serverStream.Read(buffer, 0, 103);
                    aTemp.ArrayToObjetc(buffer);
                    lByte.Add(aTemp.getMSG());
                    serverStream.Write(aTemp.ObjetcToArray(), 0, 103);
                    serverStream.Flush();
                }

                
                foreach (byte[] it in lByte)
                {
                    msj += Encoding.ASCII.GetString(it);
                }
                msj = msj.Replace("\u0000", "");

                m = msj.Split(new String[] { "\n" }, StringSplitOptions.None);

                clientSocket.Close();
            }
            catch (Exception e)
            {
                Console.Out.WriteLine(e.Message);
            }

            json = jsonSerializer.Serialize(m);
            return json;
        }
    }
}
