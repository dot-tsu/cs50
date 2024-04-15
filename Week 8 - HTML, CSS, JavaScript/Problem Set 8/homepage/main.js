// script.js
document.addEventListener('DOMContentLoaded', function () {
    const cursor = document.createElement('div');
    cursor.classList.add('custom-cursor');
    document.body.appendChild(cursor);

    document.addEventListener('mousemove', function (e) {
        cursor.style.left = e.pageX + 'px';
        cursor.style.top = e.pageY + 'px';
    });

    const links = document.querySelectorAll('a');
    links.forEach(link => {
        link.addEventListener('mouseover', function () {
            cursor.style.transform = 'scale(4)';
        });
        link.addEventListener('mouseleave', function () {
            cursor.style.transform = 'scale(1)';
        });
    });
});
