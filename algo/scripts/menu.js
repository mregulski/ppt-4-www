function toggleMenu() {
    var el = document.getElementById("menu");
    if(el.style.display != 'block')
        el.style.display = 'block';
    else
        el.style.display = 'none';
}

window.onload = function() {
    document.getElementById("menuToggle").onclick = toggleMenu;
}
