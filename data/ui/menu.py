import rocket

from BallisticUI import UI

def bind_menu(event):
    menu = event.current_element.GetElementById('top-toolbar')
    li_tags = menu.GetElementsByTagName('li')
    for li in li_tags:
        li.AddEventListener('click', "unfold(event)")

def hide_items():
    doc = UI.get_instance().get_document("top-toolbar")
    li_tags = doc.get_document().GetElementsByTagName('li')
    for li in li_tags:
        li.class_name = ''
    
def unfold(event):
    hide_items()
    event.current_element.class_name='active'

