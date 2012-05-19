SLB.using(SLB)

-- Draw Function
function draw()
	gl.Begin( "GL_LINES" )

	gl.Color( 1.0, 0.0, 1.0 )
	gl.Vertex( 10.0, 10.0 )
	gl.Color( 1.0, 0.0, 0.0 )
	gl.Vertex( 190.0, 10.0 )
	
	gl.Color( 1.0, 1.0, 0.0 )
	gl.Vertex( 10.0, 15.0 )
	gl.Color( 0.0, 1.0, 1.0 )
	gl.Vertex( 190.0, 15.0 )
	
	gl.End()
end
