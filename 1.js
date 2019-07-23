;(function() {
	'use strict';

})();
// подложка под всплывающее окно
var overlay	= document.querySelector('.overlay'),
	// коллекция всех элементов на странице, которые могут открывать всплывающие окна
	// их отличительной особенность является наличие атрибута '[data-modal]'
	mOpen	= document.querySelectorAll('[data-modal]'),
	// коллекция всех элементов на странице, которые могут закрывать всплывающие окна
	// их отличительной особенность является наличие атрибута '[data-close]'
	mClose	= document.querySelectorAll('[data-close]'),
	// флаг всплывающего окна: false - окно закрыто, true - открыто
	mStatus	= false;

	// если нет элементов управления всплывающими окнами, прекращаем работу скрипта
	if (mOpen.length == 0) return;
  [].forEach.call(mOpen, function(el) {
	// вешаем обработчик события на каждый элемент коллекции
	el.addEventListener('click', function(e) {
		// получаем значение атрибута ['data-modal'], которое
		// является id всплывающего окна
		var modalId	= el.getAttribute('data-modal'),
			// используя id, получаем объект всплывающего окна,
			// которое мы собираемся открыть
			modal	= document.getElementById(modalId);

		// вызываем функцию открытия всплывающего окна, аргументом
		// является объект всплывающего окна
		modalShow(modal);

	});
});
<script>var typeAnimate = 'fade';</script>
function modalShow(modal) {
	// показываем подложку всплывающего окна
	overlay.classList.remove('fadeOut');
	overlay.classList.add('fadeIn');
	// определяем тип анимации появления всплывающего окна
	// убираем и добавляем классы, соответствующие типу анимации
	if (typeAnimate == 'fade') {
		modal.classList.remove('fadeOut');
		modal.classList.add('fadeIn');
	} else if (typeAnimate == 'slide') {
		modal.classList.remove('slideOutUp');
		modal.classList.add('slideInDown');
	}
	// выставляем флаг, обозначающий, что всплывающее окно открыто
	mStatus = true;
}
[].forEach.call(mClose, function(el) {
	el.addEventListener('click', modalClose);
});
document.addEventListener('keydown', modalClose);
if (mStatus && ( !event.keyCode || event.keyCode === 27 ) ) { ... }
function modalClose() {
	// проверяем выполнение условия
	if (mStatus && ( !event.keyCode || event.keyCode === 27 ) ) {
		// собираем коллекцию объектов всех всплывающих окон на странице
		var modals = document.querySelectorAll('.dlg-modal');

		// обходим по очереди каждый элемент коллекции (каждое всплывающее окно)
		// и в зависимости от типа анимации, используемой на данной странице,
		// удаляем класс анимации открытия окна и добавляем класс анимации закрытия
		[].forEach.call(modals, function(modal) {
			if (typeAnimate == 'fade') {
				modal.classList.remove('fadeIn');
				modal.classList.add('fadeOut');
			} else if (typeAnimate == 'slide') {
				modal.classList.remove('slideInDown');
				modal.classList.add('slideOutUp');
			}
		});

		// закрываем overlay
		overlay.classList.remove('fadeIn');
		overlay.classList.add('fadeOut');
		// сбрасываем флаг, устанавливая его значение в 'false'
		// это значение указывает нам, что на странице нет открытых
		// всплывающих окон
		mStatus = false;
	}
}
