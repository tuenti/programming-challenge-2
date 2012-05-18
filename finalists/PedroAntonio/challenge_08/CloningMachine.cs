/*
 * Tuenti Programming Challenge 2
 * Challenge 8: The Demented Cloning Machine
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace TuentiChallenge
{
	public class CloningMachine
	{
		private class Transformations
		{
			private string[] _map = new string[256];

			public String transform( char c )
			{
				string s = _map[(int) c];
				if ( s != null )
					return s;
				else
					return c.ToString();
			}

			public Transformations( String line )
			{
				foreach ( String t in line.Split( ',' ) )
				{
					string[] st = t.Split( new string[] { "=>" }, StringSplitOptions.None );
					char c = st[0][0];
					string s = st[1];
					_map[(int) c] = s;
				}
			}
		}

		private static List<Transformations> series;

		private class Pair<T, U>
		{
			public T t;
			public U u;
			private Pair( T t, U u )
			{
				this.t = t;
				this.u = u;
			}

			private static Stack<Pair<T, U>> _pool = new Stack<Pair<T, U>>();

			public static Pair<T, U> Instantiate( T t, U u )
			{
				if ( _pool.Count > 0 )
				{
					Pair<T, U> p = _pool.Pop();
					p.t = t;
					p.u = u;
					return p;
				}
				return new Pair<T, U>( t, u );
			}

			public static void Free( Pair<T, U> p )
			{
				_pool.Push( p );
			}
		}

		private static void dsam( String word, int prof, StreamWriter w )
		{
			Stack<Pair<String, int>> stack = new Stack<Pair<String, int>>();
			stack.Push( Pair<String, int>.Instantiate( word, prof ) );

			while ( stack.Count > 0 )
			{
				Pair<String, int> p = stack.Pop();
				String p_word = p.t;
				int p_prof = p.u;
				Pair<String, int>.Free( p );
				if ( p_prof == series.Count )
				{
					w.Write( p_word );
				}
				else
				{
					Transformations t = series[p_prof];
					for ( int i = p_word.Length - 1; i >= 0; i-- )
					{
						char c = p_word[i];
						String s = t.transform( c );
						stack.Push( Pair<String, int>.Instantiate( s, p_prof + 1 ) );
					}
				}
			}
		}

		public static void Main( String[] args )
		{
			String init = Console.ReadLine();

			series = new List<Transformations>();
			try
			{
				while ( true )
				{
					series.Add( new Transformations( Console.ReadLine() ) );
				}
			}
			catch
			{//EOF
			}

			StreamWriter writer = new StreamWriter( "out.txt" );
			dsam( init, 0, writer );
			writer.Flush();
			writer.Close();
			Console.WriteLine( GetMD5HashFromFile( "out.txt" ) );
		}

		protected static string GetMD5HashFromFile( string fileName )
		{
			FileStream file = new FileStream( fileName, FileMode.Open );
			MD5 md5 = new MD5CryptoServiceProvider();
			byte[] retVal = md5.ComputeHash( file );
			file.Close();

			StringBuilder sb = new StringBuilder();
			for ( int i = 0; i < retVal.Length; i++ )
			{
				sb.Append( retVal[i].ToString( "x2" ) );
			}
			return sb.ToString();
		}
	}
}