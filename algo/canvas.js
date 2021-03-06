window.addEventListener('resize', function() {
    canvas = document.getElementById("cnv");
    console.log('pre', canvas.width);
    var ctx = canvas.getContext('2d');
    ctx.save();
    ctx.setTransform(1,0,0,1,0,0);
    ctx.clearRect(0,0,canvas.width, canvas.height);
    canvas.width = window.innerWidth * 0.5;
    canvas.height = canvas.width;
    var scale = canvas.width/logo.width;
    
    console.log('scale:',scale);
    ctx.restore();
    logo.draw(scale);
});

var logo = (function(){
    return {
        draw: draw,
        width: 306
    };
    
    function draw(scale, canvas) {
        canvas = document.getElementById("cnv");
        if(canvas.getContext) {
            var ctx = canvas.getContext('2d');
            var seg = new Segment(scale);
            ctx.fillStyle = "#DE492A";
            ctx.save();
            ctx.translate(scale*38,scale*153)
            for(var i = 0; i < 4; i++) {
                ctx.fill(seg.path);
                ctx.rotate(Math.PI/2);
                ctx.translate(scale*(-115),scale*(-115));
            }
            ctx.restore();
        }
    }
    
    function Segment(scale) {
        this.path = path();
        this.scale = scale;
        
        function path(scale) {
            var path = new Path2D();
            console.log("path", path);
            path.addPath(circle());
            console.log("with circle", path);
            path.addPath(arrow(13,-43));
            return path;
        }
        function arrow(x, y) {
            var path = new Path2D();
            path.moveTo(scale*x,scale*y);
            // path.quadraticCurveTo(x+10, y-50, x+43, y-58);
            path.quadraticCurveTo(scale*(x+10), scale*(y-50), scale*(x+43), scale*(y-58));
            path.lineTo(scale*(x+48), scale*(y-43));
            path.lineTo(scale*(x+56), scale*(y-70));
            path.lineTo(scale*(x+27), scale*(y-75));
            path.lineTo(scale*(x+38), scale*(y-64));
            path.quadraticCurveTo(scale*(x-6), scale*(y-48), scale*(x-16), scale*(y-5));
            return path;    
        }
         function circle() {
            var path = new Path2D();
            path.arc(0, 0, scale*38, 0, 2*Math.PI);
            return path;
        }
    }
    
})();