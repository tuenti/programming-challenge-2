/*
 * Tuenti Programming Challenge 2
 * Challenge 15: Newspaper code
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

using System;
using System.Drawing;

namespace TuentiChallenge
{
	public class NewspaperCode
	{
		public static void Main( string[] args )
		{
			Bitmap bm = new Bitmap( "newspaper.png" );

			for ( int i = 0; i < bm.Width; i++ )
			{
				for ( int j = 0; j < bm.Height; j++ )
				{
					Color col = bm.GetPixel( i, j );

					if ( col.A == 0 )
						bm.SetPixel( i, j, Color.FromArgb( 255, 255, 0, 0 ) );
				}
			}

			bm.Save( "newspaper_revealed.png" );

			// "the secret has been revealed to solve the challenge which is the twentieth emirp"
		}
	}
}
