varying vec3 N;
varying vec3 v;    
 uniform sampler2D tex;
varying vec2 vTexCoord;    

varying in vec2 uv;
uniform int light_count;
uniform int use_light;
uniform int bounding;

void main (void)  
{  
  if(bounding==1) {
    gl_FragColor=vec4(0,1,0,1);
return;
   }
    
if(true) {
        gl_FragColor =   texture2D(tex, gl_TexCoord[0].st); 
        return;
     }
 vec4 amb,diff,spec; 
   
for(int i=0; i<light_count; i++) {
   
float dist=distance(v, gl_LightSource[i].position.xyz)   ; 
vec3 L = normalize(gl_LightSource[i].position.xyz - v);   
   vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)  
   vec3 R = normalize(-reflect(L,N));  
 
 float atten  = 1.0 / ( dist*dist / 10000);
   //calculate Ambient Term:  
   amb += gl_FrontLightProduct[i].ambient;    

   //calculate Diffuse Term:  
    diff += gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0)*atten;    
   
   // calculate Specular Term:
   spec += (gl_FrontLightProduct[i].specular  * pow(max(dot(R,E),0)*0.1,0.3*gl_FrontMaterial.shininess)); 
   
    
}
// write Total Color:   //gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec +
 vec4 texColor = texture2D(tex,gl_TexCoord[0].st);    
 //gl_FragColor=((diff*vec4(texColor.rgb,1.0))+(spec*texColor.a));  
texColor.rgb=vec3(diff)*vec3(texColor.rgb)+vec3(spec*texColor.a);
//texColor.a=1;
// texColor =   vec4(texColor.a) * texColor + vec4(1.0 - texColor.a)*texColor;
     gl_FragColor=texColor;
}